#pragma once
#include "constants.h"
#include "vec2.h"
#include <SDL2/SDL.h>

enum class CollisionType {
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};

struct Contact {
    CollisionType type;
    float penetration;
};

class Ball {
public:
    Ball(Vec2 position, Vec2 velocity) : position_(position), velocity_(velocity) {
        rect_.x = static_cast<int>(position_.x_);
        rect_.y = static_cast<int>(position_.y_);
        rect_.w = BALL_WIDTH;
        rect_.h = BALL_HEIGHT;
    }

    void Update(float dt) {
        position_ += velocity_ * dt;
    }

    void Draw(SDL_Renderer *renderer) {
        rect_.x = static_cast<int>(position_.x_);
        rect_.y = static_cast<int>(position_.y_);

        SDL_RenderFillRect(renderer, &rect_);
    }

    void CollideWithPaddle(Contact const &contact) {
        position_.x_ += contact.penetration;
        velocity_.x_ = -velocity_.x_;

        if (contact.type == CollisionType::Top) { // Send ball more to the side when hitting side of paddle
            velocity_.y_ = -0.75f * BALL_SPEED;
        } else if (contact.type == CollisionType::Bottom) {
            velocity_.y_ = 0.75f * BALL_SPEED;
        }
    }

    void CollideWithWall(Contact const &contact) {
        if ((contact.type == CollisionType::Top) || (contact.type == CollisionType::Bottom)) { // Bounce of walls
            position_.y_ += contact.penetration;
            velocity_.y_ = -velocity_.y_;
        } else if (contact.type == CollisionType::Left) { // Reset ball
            position_.x_ = WINDOW_WIDTH / 2.0f;
            position_.y_ = WINDOW_HEIGHT / 2.0f;
            velocity_.x_ = BALL_SPEED;
            velocity_.y_ = 0.75f * BALL_SPEED;
        } else if (contact.type == CollisionType::Right) {
            position_.x_ = WINDOW_WIDTH / 2.0f;
            position_.y_ = WINDOW_HEIGHT / 2.0f;
            velocity_.x_ = -BALL_SPEED;
            velocity_.y_ = 0.75f * BALL_SPEED;
        }
    }

    Vec2 position_;
    Vec2 velocity_;
    SDL_Rect rect_{};
};