#ifndef VECTOR_H_
#define VECTOR_H_

struct Vec2 {
    double x, y; // vector coordinates in pixels

    // dot product
    double dot (const Vec2& other) {
        return(x * other.x) + (y * other.y);
    };

    // multiplication
    Vec2 mult (double scalar) {
        return{x*scalar, y*scalar};
    };

    // subtraction
    Vec2 sub (const Vec2& other) {
        return{x - other.x, y - other.y};
    };
};












#endif
