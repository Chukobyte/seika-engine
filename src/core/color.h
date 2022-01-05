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

    static Color NormalizedColor(int red, int green, int blue) {
        return Color(red / 255.0f, green / 255.0f, blue / 255.0f);
    }

    static Color NormalizedColor(int red, int green, int blue, int alpha) {
        return Color(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
    }

    Color operator*(float value) {
        return Color(this->r * value, this->g * value, this->b * value, this->a);
    }
};

#endif //COLOR_H
