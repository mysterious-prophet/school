#include <stdio.h>
#include <stdlib.h>
#include <fstream> // load from file
#include <iostream> // std::cout
#include <sstream> // load from file
#include <string> // load from file
#include <time.h> // evals comparison
#include <vector> // matrix values storing
#include <algorithm> //std::max
#include <numeric> //std::accumulate for vector sum

#include <cuda_runtime.h>
#include <device_launch_parameters.h>


// matrix dimension setting for the whole program
// shared memory in CUDA opt. requires compile time const. - global const.
// also define type of values in matrix for further optimization
// GPUs are optimized for single precision floating point - float is better than int or double
const int max_dim = 1 << 10;
typedef float matrix_vals_type;


// simple matrix structure using human friendly 2d vectors for values
struct simpleMatrix {
	unsigned int n = 0;
	unsigned int m = 0;
	std::vector<std::vector<matrix_vals_type>> values;

	simpleMatrix() {};
	simpleMatrix(unsigned int m,unsigned int n)
		:m(m), n(n)
	{
		values.resize(m, std::vector<matrix_vals_type>(n));
	}
};

// optimized matrix structure using 1d vectors for values
struct optMatrix {
	int n = 0;
	std::vector<matrix_vals_type> values; // optimization by using 1d vector

	optMatrix() {};
	optMatrix(const int n)
		:n(n)
	{
		values.resize(n * n);
	}
};


// load simple 2d matrix into a vector from a file
simpleMatrix loadSimpleMatrix(std::string filename) {
	std::ifstream input_file(filename);
	if (input_file.is_open()) {
		simpleMatrix matrix {};
		std::string line;

		while (std::getline(input_file, line)) {
			matrix_vals_type value;
			std::vector<matrix_vals_type> row;
			std::istringstream line_stream(line);
			while (line_stream >> value) {
				row.push_back(value);
			}
			matrix.values.push_back(row);
		}

		matrix.m = matrix.values.size();
		matrix.n = matrix.values[0].size();
		return matrix;
	}
	else {
		printf("Matrix could not be loaded! No such file: %s", filename);
	}
}


// generate random simple matrix of size m, n with int values from 1 to max_val
std::vector<std::vector<matrix_vals_type>> getRandomSimpleMatrixValues(const int& m, const int& n, const int& max_val) {
	std::vector<std::vector<matrix_vals_type>> values(m, std::vector<matrix_vals_type>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			values[i][j] = rand() % max_val + 1;
		}
	}
	return values;
}


// overload to have same simpleMatrix values as already obtained optMatrix values
std::vector<std::vector<matrix_vals_type>> getRandomSimpleMatrixValues(const int& m, const int& n, const optMatrix& matrix) {
	std::vector<std::vector<matrix_vals_type>> values(m, std::vector<matrix_vals_type>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			values[i][j] = matrix.values[i * max_dim + j];
		}
	}
	return values;
}

// generate random opt. matrix of size n, n with int values from 1 to max_val
std::vector<matrix_vals_type> getRandomOptMatrixValues(const int& n, const int& max_val) {
	std::vector<matrix_vals_type> values(n * n);
	std::generate(values.begin(), values.end(), [max_val]() {return rand() % max_val + 1; });
	return values;
}


// print simple matrix to console
void printSimpleMatrix(simpleMatrix& matrix) {
	for (int i = 0; i < matrix.m; i++) {
		for (int j = 0; j < matrix.n; j++) {
			std::cout << matrix.values[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// print opt. matrix to console
void printOptMatrix(optMatrix& matrix) {
	for (int i = 0; i < matrix.n * matrix.n; i += max_dim) {
		for (int j = 0; j < matrix.n; j++) {
			std::cout << matrix.values[i + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


// check whether simple matrices have compatible dimensions
inline bool checkDims(simpleMatrix& matrix_A, simpleMatrix& matrix_B) {
	return (matrix_A.n == matrix_B.m);
}


// multiply matrices using standard CPU multiplication
// most naive approach using 2d vectors (still faster than 2d dynamic arrays though)
// still passing by reference though
// unsigned is slower than int
simpleMatrix matrixSimpleMultCPU(simpleMatrix& matrix_A, simpleMatrix& matrix_B) {
	simpleMatrix matrix_C(matrix_A.m, matrix_B.n);

	for (unsigned int i = 0; i < matrix_A.m; i++) {
		for (unsigned int j = 0; j < matrix_B.n; j++) {
			for (unsigned int k = 0; k < matrix_A.n; k++) {
				matrix_C.values[i][j] += matrix_A.values[i][k] * matrix_B.values[k][j];
			}
		}
	}

	return matrix_C;
}


// optimized cpu matrix multiplication
// 1d vectors with optimized indexing instead of 2d vectors
// using int instead of unsigned is faster
// not accesing optMatrix struct in for cycles by substituting int n = matrix_C.n
// declaring iterators ahead of cycles, k = k_block is faster than k = 0
// using submatrix_C instead of accesing matrix_C structure
// switching k (cols of A, rows of B) and j (rows of A, cols of B) cycles - switching j most frequently is better for cache access as c++ is row major language
// using block submatrices for faster cache access
// using pragma unroll
optMatrix matrixOptMultCPU(optMatrix& matrix_A, optMatrix& matrix_B) {
	optMatrix matrix_C(matrix_A.n);
	int n = matrix_C.n;

	int submatrix_size = 1 << 8;
	int k_block = 0, j_block = 0, i = 0, k = k_block, j = j_block;

	matrix_vals_type submatrix_A = 0;
	for (k_block = 0; k_block < n; k_block += submatrix_size) {
		for (j_block = 0; j_block < n; j_block += submatrix_size) {
			for (i = 0; i < n; i++) {
				for (k = k_block; k < k_block + submatrix_size; k++) {
					// A[i][k]
					submatrix_A = matrix_A.values[i * n + k];
#pragma unroll(8)
					for (j = j_block; j < j_block + submatrix_size; j++) {
						// C[i][j] = A[i][k] * B[k][j]
						matrix_C.values[i * n + j] += submatrix_A * matrix_B.values[k * n + j];
					}
				}
			}
		}
	}

	/*int i = 0, int j = 0, int k = 0;
	matrix_vals_type submatrix_C = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			submatrix_C = 0;
#pragma unroll
			for (k = 0; k < n; k++) {
				submatrix_C += matrix_A.values[i * n + k] * matrix_B.values[k * n + j];
			}
			matrix_C.values[i * n + j] = submatrix_C;
		}
	}*/

	/*int i = 0, int j = 0, int k = 0;
	matrix_vals_type submatrix_C = 0;
	for (i = 0; i < n; i++) {
	for (k = 0; k < n; k++) {
		//submatrix_C = 0;
		for (j = 0; j < n; j++) {
			matrix_C.values[i * n + j] += matrix_A.values[i * n + k] * matrix_B.values[k * n + j];
			//submatrix_C += matrix_A.values[i * n + k] * matrix_B.values[k * n + j];
		}
		//matrix_C.values[i * n + j] = submatrix_C;
	}
	}*/

	return matrix_C;
}

// simple CUDA matrix multiplication
// indexing by CUDA blocks and threads equivalent to CPU opt. multiplication
// CUDA kernel cannot return anything - void, memcpy in driver necessary
// kernel is introduced using __global__ keyword
__global__ 
void matrixSimpleMultCUDA(const int max_size, const matrix_vals_type* matrix_a, const matrix_vals_type* matrix_b, matrix_vals_type* matrix_c) {
	// row and col indices from <blocks, threads> kernel input
	// blockDim = #of threads in a block
	// blockIdx = number of block within its specific grid (represents matrix here)
	// threadIdx = number of thread within its specific block
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	matrix_vals_type submatrix_c = 0;
	if (row < max_size && col < max_size) {
		// we access rows and cols through blocks and threads and have to iterate through both to get one element of resulting matrix
		for (int i = 0; i < max_size; i++) {
			// [row][i], [i][col]
			submatrix_c += matrix_a[row * max_size + i] * matrix_b[i * max_size + col];
		}
	}
	matrix_c[row * max_size + col] = submatrix_c;
}


// optimized CUDA matrix multiplication
// using matrix_vals_type float - faster than double or int
// using 1d static shared memory submatrices 
// unrolling multiplication for cycle
// using vars for threadIdx, blockIdx, blockDim improves performance slightly - not worth it?
// (i + tiy) * max_size is better than version withou parantheses
__global__
void matrixOptMultCUDA(const int max_size, const matrix_vals_type* matrix_a, const matrix_vals_type* matrix_b, matrix_vals_type* matrix_c) {
	// declaring these vars in advance provides slight performance improvement
	int tiy = threadIdx.y;
	int tix = threadIdx.x;
	int biy = blockIdx.y;
	int bix = blockIdx.x;
	int bdy = blockDim.y;
	int bdx = blockDim.x;

	int row = biy * bdy + tiy;
	int col = bix * bdy + tix;

	// using (static) shared memory is faster than global memory
	// https://developer.nvidia.com/blog/using-shared-memory-cuda-cc/
	// all threads in the block have access to the same shared memory
	// To ensure correct results when parallel threads cooperate, we must synchronize the threads. CUDA provides a simple barrier synchronization primitive, __syncthreads(). A thread�s execution can only proceed past a __syncthreads() after all threads in its block have executed the __syncthreads()
	// could also be implemented as 2d - no improvement
	__shared__ matrix_vals_type shared_a[max_dim];
	__shared__ matrix_vals_type shared_b[max_dim];

	matrix_vals_type submatrix_c = 0;
	int i = 0, j = 0;
	for (i = 0; i < max_size; i += bdx) {
		// shared memory is relevant for threads in one block ergo indexing as [tiy][tix] -> [tiy * bdx + tix]
		// further indexing by i subdivisions [row][i + tix], [i + tiy][col]
		shared_a[tiy * bdy + tix] = matrix_a[row * max_size + i + tix];
		shared_b[tiy * bdy + tix] = matrix_b[col + (i + tiy) * max_size];

		// synchronize before computation
		__syncthreads();

		// try unrolling cycle
		// j is defacto threadIdx bounded by its blockDim
#pragma unroll
		for (j = 0; j < bdx; j++) {
			// [tiy][j], [j][tix]
			submatrix_c += shared_a[tiy * bdy + j] * shared_b[j * bdx + tix];
		}

		// synchronize after computation
		__syncthreads();
	}

	matrix_c[row * max_size + col] = submatrix_c;
}

// CUDA matrix multiplication preparation and driver
optMatrix matrixMultCUDADriver(bool opt, const int num_threads, const int num_blocks, size_t byte_size, optMatrix& matrix_A, optMatrix& matrix_B) {
	optMatrix matrix_C(matrix_A.n);

	// alloc. memory in CUDA capable nVidia GPU
	matrix_vals_type* matrix_a, * matrix_b, * matrix_c;
	cudaMalloc(&matrix_a, byte_size);
	cudaMalloc(&matrix_b, byte_size);
	cudaMalloc(&matrix_c, byte_size);

	// copy data from CPU (host) to GPU (device)
	cudaMemcpy(matrix_a, matrix_A.values.data(), byte_size, cudaMemcpyHostToDevice);
	cudaMemcpy(matrix_b, matrix_B.values.data(), byte_size, cudaMemcpyHostToDevice);

	// creating 2d grids for matrix rows and cols
	dim3 threads(num_threads, num_threads);
	dim3 blocks(num_blocks, num_blocks);

	// using optimized or unonptimized variant of CUDA multiplication kernel
	if(!opt)
		matrixSimpleMultCUDA << <blocks, threads >> > (max_dim, matrix_a, matrix_b, matrix_c);
	else
		matrixOptMultCUDA << <blocks, threads>> > (max_dim, matrix_a, matrix_b, matrix_c);
	
	// copy result back from GPU to matrix_C on CPU
	cudaMemcpy(matrix_C.values.data(), matrix_c, byte_size, cudaMemcpyDeviceToHost);

	// free GPU memory
	cudaFree(matrix_a);
	cudaFree(matrix_b);
	cudaFree(matrix_c);

	return matrix_C;
}

// check whether the results are the same
inline bool checkResults(optMatrix& matrix_1, optMatrix& matrix_2) {
	//return (matrix_1.values == matrix_2.values);

	int errs = 0;
	for (int i = 0; i < matrix_1.values.size(); i++) {
		matrix_1.values[i] = std::round(matrix_1.values[i]);
		matrix_2.values[i] = std::round(matrix_2.values[i]);
		if (matrix_1.values[i] != matrix_2.values[i]) {
			printf("Warning: value mismatch: %f vs. %f on index: %i \n", matrix_1.values[i], matrix_2.values[i], i);
			errs++;
		}
		
	}
	if (errs > 0)
		return false;
	else
		return true;
}


// calculate multiplication elapsed time
inline double calcElapsedTime(const clock_t& start_time, const clock_t& end_time) {
	return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}


// calculate multiplication average time
inline double calcAvgTime(const int num_evals, std::vector<double> measured_times) {
	return std::accumulate(measured_times.begin(), measured_times.end(), decltype(measured_times)::value_type(0)) / num_evals;
}


// calculate optimization time saving
inline double calcSaving(const double& opt_avg_time, const double& simple_avg_time) {
	return (1 - opt_avg_time / simple_avg_time) * 100;
}

// calculate optimization performance improvement
inline double calcPerf(const double& opt_avg_time, const double& simple_avg_time) {
	return 1 / (opt_avg_time / simple_avg_time);
}

int main() {
	// number of evaluation runs
	int num_evals = 10;

	// load matrices from files
	//matrix_A = loadMatrix("matrix_A.txt");
    //matrix_B = loadMatrix("matrix_B.txt");

	// generate random matrices of following specs
	int max_value = 100;
	int matrix_A_m = max_dim;
	int matrix_A_n = max_dim;
	int matrix_B_m = matrix_A_n;
	int matrix_B_n = max_dim;
	//int max_dim = std::max(std::max(matrix_A_m, matrix_A_n), matrix_B_n);

	// CUDA parameters
	size_t byte_size = max_dim * max_dim * sizeof(matrix_vals_type);
	int num_blocks = 32;
	int num_threads = max_dim / num_blocks;

	// initialize matrices
	simpleMatrix simple_matrix_A(matrix_A_m, matrix_A_n);
	simpleMatrix simple_matrix_B(matrix_B_m, matrix_B_n);
	simpleMatrix simple_matrix_C(matrix_A_m, matrix_B_n);

	optMatrix opt_matrix_A(matrix_A_n);
	optMatrix opt_matrix_B(matrix_A_n);
	optMatrix opt_matrix_C_cpu(matrix_A_n);
	optMatrix opt_matrix_C_cuda_simple(matrix_A_n);
	optMatrix opt_matrix_C_cuda_opt(matrix_A_n);

	// generate random matrices
	std::srand(time(NULL));
	/*simple_matrix_A.values = getRandomSimpleMatrixValues(matrix_A_m, matrix_A_n, max_value);
	simple_matrix_B.values = getRandomSimpleMatrixValues(matrix_B_m, matrix_B_n, max_value);
	opt_matrix_A.values = getRandomOptMatrixValues(matrix_A_n, max_value);
	opt_matrix_B.values = getRandomOptMatrixValues(matrix_B_n, max_value);*/

	printf("CPU, CUDA matrix multiplication of max. dim: %d comparison: \n", max_dim);
	if (!checkDims(simple_matrix_A, simple_matrix_B)) {
		printf("Matrices have incompatible size for multiplication! \n Exiting...");
		return 1;
	}
	else {
		// debug print
		//printf("Multiplying matrices: \n");
		//printf("Matrix A: \n");
		//printMatrix(matrix_A);
		//printf("Matrix B: \n");
		//printMatrix(matrix_B);

		// initialize vectors for time measuring
		std::vector<double> simple_cpu_times_arr(num_evals, 0);
		std::vector<double> simple_cpu_times_vect(num_evals, 0);
		std::vector<double> opt_cpu_times(num_evals, 0);
		std::vector<double> simple_cuda_times(num_evals, 0);
		std::vector<double> opt_cuda_times(num_evals, 0);

		// initialize time variables
		clock_t start_time, end_time;
		double elapsed_time;

		for (int i = 0; i < num_evals; i++) {
			opt_matrix_A.values = getRandomOptMatrixValues(matrix_A_n, max_value);
			opt_matrix_B.values = getRandomOptMatrixValues(matrix_B_n, max_value);
			simple_matrix_A.values = getRandomSimpleMatrixValues(matrix_A_m, matrix_A_n, opt_matrix_A);
			simple_matrix_B.values = getRandomSimpleMatrixValues(matrix_B_m, matrix_B_n, opt_matrix_B);



			printf("Cycle %d/%d: \n", i + 1, num_evals);

			// simple CPU multiplication evals
			start_time = clock();
			simple_matrix_C = matrixSimpleMultCPU(simple_matrix_A, simple_matrix_B);
			end_time = clock();
			elapsed_time = calcElapsedTime(start_time, end_time);
			simple_cpu_times_vect.push_back(elapsed_time);
			printf("simple CPU vector multiplication time [s]: %4.3f \n", elapsed_time);
			//printf("Result, matrix C: \n");
			//printSimpleMatrix(simple_matrix_C);
			
			// opt. CPU multiplication evals
			start_time = clock();
			opt_matrix_C_cpu = matrixOptMultCPU(opt_matrix_A, opt_matrix_B);
			end_time = clock();
			elapsed_time = calcElapsedTime(start_time, end_time);
			opt_cpu_times.push_back(elapsed_time);
			printf("opt. CPU multiplication time [s]: %4.3f \n", elapsed_time);
			//printf("Result, matrix C: \n");
			//printOptMatrix(opt_matrix_C);

			// simple CUDA multiplication evals
			bool opt = false;
			start_time = clock();
			opt_matrix_C_cuda_simple = matrixMultCUDADriver(opt, num_threads, num_blocks, byte_size, opt_matrix_A, opt_matrix_B);
			end_time = clock();
			elapsed_time = calcElapsedTime(start_time, end_time);
			simple_cuda_times.push_back(elapsed_time);
			printf("simple CUDA multiplication time [s]: %4.3f \n", elapsed_time);
			//printf("Result, matrix C: \n");
			//printOptMatrix(opt_matrix_C);
			if (!checkResults(opt_matrix_C_cpu, opt_matrix_C_cuda_simple))
				printf("Warning: Results differ! \n");

			// opt. CUDA multiplication evals
			opt = true;
			start_time = clock();
			opt_matrix_C_cuda_opt = matrixMultCUDADriver(opt, num_threads, num_blocks, byte_size, opt_matrix_A, opt_matrix_B);
			end_time = clock();
			elapsed_time = calcElapsedTime(start_time, end_time);
			opt_cuda_times.push_back(elapsed_time);
			printf("opt. CUDA multiplication time [s]: %4.3f \n \n", elapsed_time);
			//printf("Result, matrix C: \n");
			//printOptMatrix(opt_matrix_C);
			if (!checkResults(opt_matrix_C_cpu, opt_matrix_C_cuda_opt))
				printf("Warning: Results differ! \n");
		}

		// summary of runs
		printf("\nSummary: \n");

		double simple_cpu_avg_time = calcAvgTime(num_evals, simple_cpu_times_vect);
		printf("Avg. simple CPU multiplication time [s] of matrices of max. dim.: %d over %d iters.: %4.3f \n", max_dim, num_evals, simple_cpu_avg_time);
		
		double opt_cpu_avg_time = calcAvgTime(num_evals, opt_cpu_times);
		printf("Avg. opt. CPU multiplication time [s] of matrices of max. dim.: %d over %d iters.: %4.3f \n", max_dim, num_evals, opt_cpu_avg_time);

		double simple_cuda_avg_time = calcAvgTime(num_evals, simple_cuda_times);
		printf("Avg. simple CUDA multiplication time [s] of matrice of max. dim.: %d over %d iters.: %4.3f \n", max_dim, num_evals, simple_cuda_avg_time);

		double opt_cuda_avg_time = calcAvgTime(num_evals, opt_cuda_times);
		printf("Avg. opt. CUDA multiplication time [s] of matrice of max. dim.: %d over %d iters.: %4.3f \n", max_dim, num_evals, opt_cuda_avg_time);

		/*double cpu_opt_saving = calcSaving(opt_cpu_avg_time, simple_cpu_avg_time);
		printf("CPU optimization improves speed by app. %4.2f %%! \n", cpu_opt_saving);

		double cuda_opt_saving = calcSaving(opt_cuda_avg_time, simple_cuda_avg_time);
		printf("CUDA optimization improves speed by app. %4.2f %%! \n", cuda_opt_saving);

		double total_opt_saving = calcSaving(opt_cuda_avg_time, simple_cpu_avg_time);
		printf("Total optimization improves speed by app. %4.2f %%! \n", total_opt_saving);*/

		double cpu_perf_imp = calcPerf(opt_cpu_avg_time, simple_cpu_avg_time);
		printf("CPU optimization improves performace %4.2f times! \n", cpu_perf_imp);

		double cuda_perf_imp = calcPerf(opt_cuda_avg_time, simple_cuda_avg_time);
		printf("CUDA optimization improves performace %4.2f times! \n", cuda_perf_imp);

		double total_perf_imp = calcPerf(opt_cuda_avg_time, simple_cpu_avg_time);
		printf("Total optimization improves performace %4.2f times! \n", total_perf_imp);

		// result debug print
		//printf("Result, matrix C: \n");
		//printOptMatrix(opt_matrix_C);
		return 0;
	}
}