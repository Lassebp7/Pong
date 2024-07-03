#pragma once
#include "constants.h"
#include "vec2.h"
#include <SDL2/SDL.h>

class Paddle {
public:
    Paddle(Vec2 position, Vec2 velocity) : position_(position), velocity_(velocity) {
        rect_.x = static_cast<int>(position.x_);
        rect_.y = static_cast<int>(position.y_);
        rect_.w = PADDLE_WIDTH;
        rect_.h = PADDLE_HEIGHT;
    }

    void Update(float dt) {
        position_ += velocity_ * dt;

        if (position_.y_ < 0)
            position_.y_ = 0;
        else if (position_.y_ > (WINDOW_HEIGHT - PADDLE_HEIGHT))
            position_.y_ = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }

    void Draw(SDL_Renderer *renderer) {
        rect_.y = static_cast<int>(position_.y_);

        SDL_RenderFillRect(renderer, &rect_);
    }

    Vec2 position_;
    Vec2 velocity_;
    SDL_Rect rect_{};
};
