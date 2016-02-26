#include "mandelbrot.hpp"


int iter_for_point(const std::complex<double> &c, const int MAX_ITER) {
    
    int i = 0;
    std::complex<double> z_i = 0;
    double sqr_abs = pow(real(z_i), 2) + pow(imag(z_i), 2);

    while ((i < MAX_ITER) && (sqr_abs < 4)) {
        std::complex<double> sqr = z_i * z_i;
        z_i = sqr + c;
        ++i;
        sqr_abs = pow(real(z_i), 2) + pow(imag(z_i), 2);
    }
    
    return i;
}


double norm_iter_for_point(const std::complex<double> &c, const int MAX_ITER) {
    
    return static_cast<double>(iter_for_point(c, MAX_ITER)) / MAX_ITER;
}


void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        const char* file_name) {
    
    
    cimg_library::CImg<unsigned char> img(width, height, 1, 3);
    
    const double dy = (y2 - y1) / height;
    const double dx = (x2 - x1) / width;
    
    double y = y2;
    
    for (int32_t i = 0; i < height; ++i) {
        double x = x1;
        
        for (int32_t j = 0; j < width; ++j) {
            std::complex<double> z(x, y);
            const double norm_pnt = norm_iter_for_point(z);
            x += dx;
            
            const double clr = pow(1 - norm_pnt, 3);
            const unsigned char color = (unsigned char)(clr * 255);
            img(j, i, 0) = color;           //red
            img(j, i, 1) = color;           //green
            img(j, i, 2) = color;           //blue
            
        }
        
        y -= dy;
    }
    
    img.save_png(file_name);
}