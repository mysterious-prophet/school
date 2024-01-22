#include "fractals.h"

#include <complex>

bool diverg(std::complex<double> &c){
    return (abs(c) >= 2);
}

int mandelbrot(double cre, double cim, unsigned int k, unsigned int e){
    std::complex<double> z(0, 0), c(cre, cim);
    for(unsigned int i = 0; i < k; i++){
        z = pow(z, e) + c;
        if(diverg(z))
            return z.real();
    }
    return 0;
}

int julia(double zre, double zim, double cre, double cim, unsigned int k){
    std::complex<double> z(zre, zim), c(cre, cim);
    for(unsigned int i = 0; i < k; i++){
        z = z*z + c;
        if(diverg(z))
            return z.real();
    }
    return 0;
}
