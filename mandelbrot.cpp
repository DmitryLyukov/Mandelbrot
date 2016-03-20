#include "mandelbrot.hpp"


size_t iter_for_point(const double re, const double im, const size_t MAX_ITER) {
    
    const std::complex<double> c(re, im);
    
    const double abs_c = abs(c - 0.25);
    if (abs_c * 2 < 1 - (re - 0.25) / abs_c) {
        return MAX_ITER;
    }
    if ((re + 1.) * (re + 1.) + im * im < 1/16.) {
        return MAX_ITER;
    }
    
    int i = 1;
    std::complex<double> z_i = c;
    double sqr_abs = re * re + im * im;

    while ((i < MAX_ITER) && (sqr_abs < 4)) {
        z_i = z_i * z_i + c;
        ++i;
        sqr_abs = real(z_i) * real(z_i) + imag(z_i) * imag(z_i);
    }
    
    return i;
}


void find_colors(const size_t iter, ColorMapElement &color_elem,
        const int palette, const size_t MAX_ITER) {
            
    const double norm_iter = 1. - static_cast<double>(iter) / MAX_ITER;
    const double norm_clr = pow(norm_iter, palette);
    const unsigned char color = static_cast<unsigned char>(norm_clr * 255);
    
    color_elem.red   = color;
    color_elem.green = color;
    color_elem.blue  = color;
    
    color_elem.use   = true;
}


void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        std::vector<ColorMapElement> &colormap,
        const char* file_name, const bool progress_bar,
        const int palette, const size_t MAX_ITER) {
    
    cimg_library::CImg<unsigned char> img(width, height, 1, 3);
    
    const double dy = (y2 - y1) / height;
    const double dx = (x2 - x1) / width;
    
    const size_t horiz_steps = 60;
    const size_t line_for_one_step = width / horiz_steps * 4 / 3;
    const double pr_bar_dx = (x2 - x1) / horiz_steps;
    
    double y = y2;
    
    for (int32_t i = 0; i < height; ++i) {
        double x = x1;
        
        if (progress_bar && ((i + 1) % line_for_one_step == 0)) {
            double pr_bar_x = x1;
            for (size_t j = 0; j < horiz_steps; ++j) {
                if (iter_for_point(pr_bar_x, y, MAX_ITER) > MAX_ITER * 19 / 20)
                     { std::cout << '#'; }
                else { std::cout << ' '; }
                pr_bar_x += pr_bar_dx;
            }
            std::cout << std::endl;
        }
        
        for (int32_t j = 0; j < width; ++j) {
            const size_t iter = iter_for_point(x, y, MAX_ITER);
            
            if (!colormap[iter].use) {
                find_colors(iter, colormap[iter], palette, MAX_ITER);
            }
            
            img(j, i, 0) = colormap[iter].red;
            img(j, i, 1) = colormap[iter].green;
            img(j, i, 2) = colormap[iter].blue;
            
            x += dx;
        }
        
        y -= dy;
    }
    
    img.save_png(file_name);
}