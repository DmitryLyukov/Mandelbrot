#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <vector>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>

#include "CImg.h"


int iter_for_point(const std::complex<double> &c, const int MAX_ITER = 500);

double norm_iter_for_point(const double Re, const double Im, 
                           const int MAX_ITER = 500);

void find_colors(const double norm_clr,
        unsigned char &red, unsigned char &green, unsigned char &blue,
        const int palette = 3);

void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        const char* file_name, const bool progress_bar,
        const int palette = 3);


#endif  // MANDELBROT_HPP
