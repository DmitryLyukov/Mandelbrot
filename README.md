# Mandelbrot
Простое приложение для рисования [множества Мандельброта](https://ru.wikipedia.org/wiki/%D0%9C%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%BE_%D0%9C%D0%B0%D0%BD%D0%B4%D0%B5%D0%BB%D1%8C%D0%B1%D1%80%D0%BE%D1%82%D0%B0) с использованием библиотеки [CImg](http://cimg.eu/).


Формат команды:

`./Mandelbrot <width> <height> <name_of_file> <progress_bar> <x1> <x2> <y1> <y2>`, где

`<width> <height>` - размер изображения,

`<name_of_file>` - название выходного файла,

`<progress_bar>` - 0 или 1, включение/выключение прогресс-бара,

`<x1> <x2> <y1> <y2>` - границы участка множества.

Данные параметры необязательны, по умолчанию будут применены значения: `1280 720 mandelbrot.png 0 -2 1 -1 1`.

Результатом работы программы является png-файл с изображением выбранного участка множества.

![Travis status](https://travis-ci.org/DmitryLyukov/Mandelbrot.svg)