all:
	g++-4.8 -o Mandelbrot main.cpp mandelbrot.cpp -Ofast -L/usr/X11R6/lib -lm -lpthread -lX11 -std=c++11 -ffinite-math-only -funsafe-math-optimizations -march=native -flto -fwhole-program