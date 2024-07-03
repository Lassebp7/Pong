#pragma once
#include "vec2.h"
#include <SDL2/SDL.h>

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