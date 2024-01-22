#ifndef FRACTALS_H
#define FRACTALS_H

enum FractalType{
    MANDELBROT,
    JULIA
};

int mandelbrot(double cre, double cim, unsigned int k, unsigned int e);
int julia(double zre, double zim, double cre, double cim, unsigned int k);

#endif // FRACTALS_H
