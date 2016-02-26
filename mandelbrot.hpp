#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <vector>
#include <cmath>
#include <complex>
#include <cstdint>
#include "CImg.h"


int iter_for_point(const std::complex<double> &c, const int MAX_ITER = 500);

double norm_iter_for_point(const std::complex<double> &c, const int MAX_ITER = 500);

void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        const char* file_name);


#endif  // MANDELBROT_HPP
