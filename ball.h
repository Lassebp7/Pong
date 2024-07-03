#pragma once
#include <SDL2/SDL.h>

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

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

class Ball {
public:
    Ball(Vec2 position) : position_(position) {
        rect_.x = static_cast<int>(position_.x_);
        rect_.y = static_cast<int>(position_.y_);
        rect_.w = BALL_WIDTH;
        rect_.h = BALL_HEIGHT;
    }

    void Draw(SDL_Renderer *renderer) {
        rect_.x = static_cast<int>(position_.x_);
        rect_.y = static_cast<int>(position_.y_);

        SDL_RenderFillRect(renderer, &rect_);
    }

    Vec2 position_;
    SDL_Rect rect_{};
};