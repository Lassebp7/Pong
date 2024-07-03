#pragma once

class Vec2 {
public:
    Vec2() : x_(0.0f), y_(0.0f) {}
    Vec2(float x, float y) : x_(x), y_(y) {}

    Vec2 operator+(Vec2 const &rhs) {
        return Vec2(x_ + rhs.x_, y_ + rhs.y_);
    }

    Vec2 &operator+=(Vec2 const &rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;

        return *this;
    }

    Vec2 operator*(float rhs) {
        return (Vec2(x_ * rhs, y_ * rhs));
    }

    float x_, y_;
};