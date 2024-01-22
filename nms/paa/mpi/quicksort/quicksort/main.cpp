#include <stdio.h>
#include <iostream> // cout
#include <vector> // sequential data
#include <random> // data rand values
#include <time.h> // rand seed
#include <algorithm> // generate
#include <numeric> // accumulate

#include <mpi.h> // MPI lib.

typedef int data_type;


// swap two elements of a vector
inline void swapDataSeq(std::vector<data_type>& data, const int i, const int j) {
	const int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}


// divide data based on pivot
int divideDataSeq(std::vector<data_type>& data, const int start_ind, const int end_ind) {
	// choose pivot as the last element 
	const int pivot_ind = end_ind;
	const int pivot = data[pivot_ind];
	int part_ind = start_ind;

	for (int i = start_ind; i < end_ind; i++) {
		if (data[i] < pivot) {
			swapDataSeq(data, i, part_ind);
			part_ind++;
		}
	}

	swapDataSeq(data, part_ind, pivot_ind);
	return part_ind;
}


// sequential quicksort driver
void quickSortSeq(std::vector<data_type>& data, const int start_ind, const int end_ind) {
	if (start_ind < end_ind) {
		const int part_ind = divideDataSeq(data, start_ind, end_ind);
		quickSortSeq(data, start_ind, part_ind - 1);
		quickSortSeq(data, part_ind + 1, end_ind);
	}
}


// swap data in array for MPI
inline void swapDataMPI(data_type* data, const int i, const int j) {
	const int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}


// merge two ordered dataset for MPI
data_type* mergeDataMPI(data_type* data1, const int size1, data_type* data2, const int size2) {
	// create merging array
	data_type* result = (data_type*)malloc((size1 + size2) * sizeof(data_type));
	int i = 0, j = 0, k;
	const int size = size1 + size2;

	// merge two arrays into one
	for (k = 0; k < size; k++) {
		if (i >= size1) {
			result[k] = data2[j];
			j++;
		}
		else if (j >= size2) {
			result[k] = data1[i];
			i++;
		}
		else if (data1[i] < data2[j]) {
			result[k] = data1[i];
			i++;
		}
		else { // (data2[j] <= data1[i]
			result[k] = data2[j];
			j++;
		}
	}

	return result;
}

// divide data for MPI based on pivot
int divideDataMPI(data_type* data, const int start_ind, const int end_ind) {
	const int pivot_ind = end_ind;
	const int pivot = data[pivot_ind];
	int part_ind = start_ind;

	for (int i = start_ind; i < end_ind; i++) {
		if (data[i] < pivot) {
			swapDataMPI(data, i, part_ind);
			part_ind++;
		}
	}

	swapDataMPI(data, part_ind, pivot_ind);
	return part_ind;
}


void quickSortMPI(data_type* data, const int start_ind, const int end_ind) {
	if (start_ind < end_ind) {
		const int part_ind = divideDataMPI(data, start_ind, end_ind);
		quickSortMPI(data, start_ind, part_ind - 1);
		quickSortMPI(data, part_ind + 1, end_ind);
	}
}


// print seq data to console
void printDataSeq(std::vector<data_type> data) {
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


// print MPI data to console
void printDataMPI(data_type* data, const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


// calculate multiplication elapsed time
inline double calcElapsedTime(const clock_t& start_time, const clock_t& end_time) {
	return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}


// calculate multiplication average time
inline double calcAvgTime(const int num_evals, std::vector<double> measured_times) {
	return std::accumulate(measured_times.begin(), measured_times.end(), decltype(measured_times)::value_type(0)) / num_evals;
}


// calculate optimization performance improvement
inline double calcPerf(const double& opt_avg_time, const double& simple_avg_time) {
	return 1 / (opt_avg_time / simple_avg_time);
}


int main(int argc, char* argv[]) {

	// set testing parameters
	const int num_evals = 5;
	int size = (int)1e6;
	srand((int)time(NULL));

	//----------------------------Sequential Quicksort----------------------------
	// initialize time measuring vars
	clock_t start_time, end_time;
	double elapsed_time;
	std::vector<double> seq_times(num_evals, 0);

	for (int i = 0; i < num_evals; i++) {
		// generate new data each iteration
		std::vector<data_type> data_seq(size, 0);
		generate(data_seq.begin(), data_seq.end(), rand);
		//printf("Cycle: %d/%d: \n", i + 1, num_evals);

		// evaluate sequentil quicksort performance
		start_time = clock();
		quickSortSeq(data_seq, 0, size - 1);
		end_time = clock();
		elapsed_time = calcElapsedTime(start_time, end_time);
		seq_times.push_back(elapsed_time);

		//printf("Sequential quicksort time [s]: %4.3f \n", elapsed_time);
		//printf("Sorted data: \n");
		//printDataSeq(data_seq);
	}

	//----------------------------MPI Quicksort----------------------------
	// run with: mpiexec -n <num_processes> quicksort.exe, e.g. mpiexec -n 8 quicksort.exe, where quicksort.exe is in Debug folder

	// initialize MPI vars
	int num_processes, rank_process;
	double mpi_time = 0;
	data_type* data_mpi = nullptr;
	std::vector<double> mpi_times(num_evals, 0);
	MPI_Status status;
	int mpi_init_stat = MPI_Init(&argc, &argv);

	if (mpi_init_stat != MPI_SUCCESS) {
		printf("Error initializing MPI. \n  Terminating... \n");
		MPI_Abort(MPI_COMM_WORLD, mpi_init_stat);
		return 1;
	}

	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_process);

	// find chunk size for all chunks on individual processess and define chunk itself
	int chunk_size = (size % num_processes == 0) ? (size / num_processes) : (size / (num_processes - 1));
	int chunk_size_own = (size >= chunk_size * (rank_process + 1)) ? chunk_size : (size - chunk_size * rank_process);
	data_type* chunk;

	// create random data once in master process
	if (rank_process == 0) {
		data_mpi = (data_type*)malloc(num_processes * chunk_size * sizeof(data_type));
		for (int i = 0; i < num_processes * chunk_size; i++) {
			if (i < size)
				data_mpi[i] = rand();
			else
				data_mpi[i] = 0;
		}
	}

	// wait for master process, synchronize 
	MPI_Barrier(MPI_COMM_WORLD);

	// start measuring MPI quicksort time
	mpi_time -= MPI_Wtime();

	// broadcast dataset size from master to all processess
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// allocate process chunk memory
	chunk = (data_type*)malloc(chunk_size * sizeof(data_type));

	// scatter chunks to processes, free memory
	MPI_Scatter(data_mpi, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
	free(data_mpi);
	data_mpi = NULL;

	// MPI quicksort chunk on process
	quickSortMPI(chunk, 0, chunk_size_own - 1);

	// send and receive chunks
	for (int j = 1; j < num_processes; j *= 2) {
		// send chunks 
		if (rank_process % (2 * j) != 0) {
			MPI_Send(chunk, chunk_size_own, MPI_INT, rank_process - j, 0, MPI_COMM_WORLD);
			break;
		}

		// receive, merge chunks
		if (rank_process + j < num_processes) {
			int chunk_size_received = (size >= chunk_size * (rank_process + 2 * j)) ? (chunk_size * j) : (size - chunk_size * (rank_process + j));
			data_type* chunk_received;
			chunk_received = (data_type*)malloc(chunk_size_received * sizeof(data_type));
			MPI_Recv(chunk_received, chunk_size_received, MPI_INT, rank_process + j, 0, MPI_COMM_WORLD, &status);
			data_mpi = mergeDataMPI(chunk, chunk_size_own, chunk_received, chunk_size_received);
			free(chunk);
			free(chunk_received);
			chunk = data_mpi;
			chunk_size_own += chunk_size_received;
		}
	}

	// time measure
	mpi_time += MPI_Wtime();

	//mpi_times.push_back(mpi_time);
		//printf("MPI quicksort time [s]: %4.3f \n", end_time - start_time);

	// print summary in master process
	if (rank_process == 0) {
		//printf("Sorted data: \n");
		//printDataMPI(chunk, chunk_size);

		printf("\nSummary: \n");

		double seq_avg_time = calcAvgTime(num_evals, seq_times);
		printf("Avg. sequential quicksort time [s] of sorting dataset of size.: %d over %d iters.: %4.3f \n", size, num_evals, seq_avg_time);

		//double mpi_avg_time = calcAvgTime(num_evals, mpi_times);
		printf("MPI quicksort time [s] of sorting dataset of size.: %d: %4.3f \n", size, mpi_time);

		double perf_imp = calcPerf(mpi_time, seq_avg_time);
		printf("Optimization improves performace %4.2f times! \n", perf_imp);
	}

	MPI_Finalize();
	return 0;
}