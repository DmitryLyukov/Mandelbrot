#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <vector>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>

#include "CImg.h"


struct ColorMapElement {
    bool use;
    unsigned char red, green, blue;
    ColorMapElement(): use(false) {}
    ~ColorMapElement() {}
};

size_t iter_for_point(const std::complex<double> &c, const size_t MAX_ITER = 500);

void find_colors(const size_t iter, ColorMapElement &color_elem,
        const int palette = 3, const size_t MAX_ITER = 500);

void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        std::vector<ColorMapElement> &colormap,
        const char* file_name, const bool progress_bar,
        const int palette, const size_t MAX_ITER);


#endif  // MANDELBROT_HPP
