#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

struct Color {
    GLfloat r = 1.0f;
    GLfloat g = 1.0f;
    GLfloat b = 1.0f;
    GLfloat a = 1.0f;
    Color() {}
    Color(GLfloat red, GLfloat green, GLfloat blue) : r(red), g(green), b(blue), a(1.0f) {}
    Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) : r(red), g(green), b(blue), a(alpha) {}
};

#endif //COLOR_H
