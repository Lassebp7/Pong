#pragma once
#include "vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class PlayerScore {
public:
    PlayerScore(Vec2 position_, SDL_Renderer *renderer, TTF_Font *font)
        : renderer_(renderer), font_(font) {
        surface_ = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
        texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);

        int width, height;
        SDL_QueryTexture(texture_, nullptr, nullptr, &width, &height);

        rect_.x = static_cast<int>(position_.x_);
        rect_.y = static_cast<int>(position_.y_);
        rect_.w = width;
        rect_.h = height;
    }

    ~PlayerScore() {
        SDL_FreeSurface(surface_);
        SDL_DestroyTexture(texture_);
    }

    void SetScore(int score) {
        SDL_FreeSurface(surface_);
        SDL_DestroyTexture(texture_);

        surface_ = TTF_RenderText_Solid(font_, std::to_string(score).c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
        texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);

        int width, height;
        SDL_QueryTexture(texture_, nullptr, nullptr, &width, &height);
        rect_.w = width;
        rect_.h = height;
    }

    void Draw() {
        SDL_RenderCopy(renderer_, texture_, nullptr, &rect_);
    }

    SDL_Renderer *renderer_;
    TTF_Font *font_;
    SDL_Surface *surface_{};
    SDL_Texture *texture_{};
    SDL_Rect rect_{};
};