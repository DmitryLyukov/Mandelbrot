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


void painting_thread(const PaintingParameters &prm, std::atomic<size_t> &line,
        std::vector<ColorMapElement> &colormap,
        cimg_library::CImg<unsigned char> &img) {
    
    while (line < prm.height) {
        size_t i = line.fetch_add(1);
        if (i >= prm.height) {
            break;
        }
        
        double x = prm.x1;
        const double y = prm.y2 - i * prm.dy;
        
        if (prm.progress_bar && ((i + 1) % prm.line_for_one_step == 0)) {
            double pr_bar_x = prm.x1;
            for (size_t j = 0; j < prm.horiz_steps; ++j) {
                if (iter_for_point(pr_bar_x, y, prm.MAX_ITER) > prm.MAX_ITER * 19 / 20)
                     { std::cout << '#'; }
                else { std::cout << ' '; }
                pr_bar_x += prm.pr_bar_dx;
            }
            std::cout << std::endl;
        }
        
        for (int32_t j = 0; j < prm.width; ++j) {
            const size_t iter = iter_for_point(x, y, prm.MAX_ITER);
            
            if (!colormap[iter].use) {
                find_colors(iter, colormap[iter], prm.palette, prm.MAX_ITER);
            }
            
            img(j, i, 0) = colormap[iter].red;
            img(j, i, 1) = colormap[iter].green;
            img(j, i, 2) = colormap[iter].blue;
            
            x += prm.dx;
        }
    }
}


void painting(const double x1, const double x2,
        const double y1, const double y2,
        const int32_t width, const int32_t height,
        std::vector<ColorMapElement> &colormap,
        const char* file_name, const bool progress_bar,
        const int palette, const size_t MAX_ITER,
        const size_t num_of_threads) {
    
    cimg_library::CImg<unsigned char> img(width, height, 1, 3);
    
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now();
    
    PaintingParameters prm;
    
    prm.MAX_ITER = MAX_ITER;
    prm.palette  = palette;
    prm.width    = width;
    prm.height   = height;
    
    prm.dy = (y2 - y1) / height;
    prm.dx = (x2 - x1) / width;
    prm.x1 = x1;
    prm.y2 = y2;
    
    prm.progress_bar = progress_bar;
    if (progress_bar) {
        prm.horiz_steps = 60;
        prm.line_for_one_step = width / prm.horiz_steps * 4 / 3;
        prm.pr_bar_dx = (x2 - x1) / prm.horiz_steps;
    }

    std::atomic<size_t> line(0);
    
    std::vector<std::thread> threads;
    for (size_t thr = 0; thr < num_of_threads; ++thr) {
        threads.push_back(std::thread (painting_thread, std::ref(prm), std::ref(line),
                                       std::ref(colormap), std::ref(img)));
    }
    for (size_t thr = 0; thr < num_of_threads; ++thr) {
        threads.at(thr).join();
    }
    
    end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> calculation_second = end_time - start_time;
    std::cout << std::endl << "Calculation time: "
              << calculation_second.count() << "s" << std::endl;
    
    start_time = std::chrono::system_clock::now();
    img.save_png(file_name);
    end_time = std::chrono::system_clock::now();
    
    std::chrono::duration<double> save_second = end_time - start_time;
    std::cout << "Time of saving: " << save_second.count() << "s" << std::endl;
}