#ifndef CANVAS_THREADS_CANVASSIZE_H
#define CANVAS_THREADS_CANVASSIZE_H


class CanvasSize {
private:
    unsigned short width;
    unsigned short height;
public:
    CanvasSize(unsigned short width,
               unsigned short height);
    CanvasSize();

    unsigned short getWidth();

    unsigned short getHeight();
};


#endif //CANVAS_THREADS_CANVASSIZE_H
