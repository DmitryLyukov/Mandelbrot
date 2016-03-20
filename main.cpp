#include <string>
#include <cstdint>
#include <cstdlib>

#include "mandelbrot.hpp"


int main(int argc, char* argv[]) {
    
    //Default initialization
    int32_t width_screen  = 1280;
    int32_t height_screen =  720;
    int palette = 3;
    std::string path_to_file("mandelbrot.png");
    bool progress_bar = false;
    double x1 = -2., x2 = 1.;
    double y1 = -1., y2 = 1.;
    size_t MAX_ITER = 500;

    for (int i = 1; i < argc; ++i) {
        if (std::string (argv[i]) == std::string("-s")) {
            width_screen  = atol(argv[++i]);
            height_screen = atol(argv[++i]);
            continue;
        }
        if (std::string (argv[i]) == std::string("-pal")) {
            palette = atoi(argv[++i]);
            continue;
        }
        if (std::string (argv[i]) == std::string("-f")) {
            path_to_file = argv[++i];
            continue;
        }
        if (std::string (argv[i]) == std::string("-bar")) {
            progress_bar = true;
            continue;
        }
        if (std::string (argv[i]) == std::string("-b")) {
            x1 = atof(argv[++i]);
            x2 = atof(argv[++i]);
            y1 = atof(argv[++i]);
            y2 = atof(argv[++i]);
            continue;
        }
        if (std::string (argv[i]) == std::string("-i")) {
            MAX_ITER = atol(argv[++i]);
            continue;
        }
    }
    
    std::vector<ColorMapElement> colormap(MAX_ITER + 1);
    
    painting(x1, x2, y1, y2, width_screen, height_screen, 
             colormap, path_to_file.c_str(), progress_bar,
             palette, MAX_ITER
    );
    
    return 0;
}
