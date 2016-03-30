#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <vector>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#include "CImg.h"


struct ColorMapElement {
    bool use;
    unsigned char red, green, blue;
    ColorMapElement(): use(false) {}
    ~ColorMapElement() {}
};

struct PaintingParameters {
    size_t MAX_ITER;
    int palette;
    size_t width, height;
    double dx, dy, x1, y2;
    bool progress_bar;
    size_t horiz_steps;
    size_t line_for_one_step;
    double pr_bar_dx;
};

size_t iter_for_point(const std::complex<double> &c, const size_t MAX_ITER = 500);

void find_colors(const size_t iter, ColorMapElement &color_elem,
        const int palette = 3, const size_t MAX_ITER = 500);

void painting_thread(const PaintingParameters &prm, std::atomic<size_t> &line,
        std::vector<ColorMapElement> &colormap,
        cimg_library::CImg<unsigned char> &img);

void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        std::vector<ColorMapElement> &colormap,
        const char* file_name, const bool progress_bar,
        const int palette, const size_t MAX_ITER,
        const size_t num_of_threads = 1);


#endif  // MANDELBROT_HPP
