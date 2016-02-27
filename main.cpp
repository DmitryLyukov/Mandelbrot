#include <string>
#include <cstdint>
#include <cstdlib>

#include "mandelbrot.hpp"

int main(int argc, char* argv[]) {
    
    int32_t width_screen  = 1280;
    int32_t height_screen =  720;
    
    if (argc > 2) {
        width_screen  = atol(argv[1]);
        height_screen = atol(argv[2]);
    }
    
    int palette = 3;
    if (argc > 3) {
        palette = atoi(argv[3]);
    }
    
    std::string path_to_file("mandelbrot.png");
    if (argc > 4) {
        path_to_file = argv[4];
    }
    
    bool progress_bar = false;
    if (argc > 5) {
        progress_bar  = atoi(argv[5]);
    }
    
    double x1 = -2., x2 = 1.;
    double y1 = -1., y2 = 1.;
    if (argc > 9) {
        x1 = atof(argv[6]);
        x2 = atof(argv[7]);
        y1 = atof(argv[8]);
        y2 = atof(argv[9]);
    }
    
    painting(x1, x2, y1, y2, width_screen, height_screen, 
             path_to_file.c_str(), progress_bar, palette
    );
    
    return 0;
}
