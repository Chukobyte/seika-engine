#ifndef COLOR_H
#define COLOR_H

#include <glad/glad.h>

class Color {
  public:
    GLfloat r = 1.0f;
    GLfloat g = 1.0f;
    GLfloat b = 1.0f;
    GLfloat a = 1.0f;

    Color() {}

    Color(GLfloat red, GLfloat green, GLfloat blue) : r(red), g(green), b(blue), a(1.0f) {}

    Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) : r(red), g(green), b(blue), a(alpha) {}

    Color operator*(float value) {
        return Color(this->r * value, this->g * value, this->b * value, this->a);
    }
};

#endif //COLOR_H
