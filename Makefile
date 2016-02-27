all:
	g++-4.8 -o Mandelbrot main.cpp mandelbrot.cpp -O3 -L/usr/X11R6/lib -lm -lpthread -lX11 -std=c++11