#include "ball.h"
#include "paddle.h"
#include "playerScore.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>

// https://austinmorlan.com/posts/pong_clone/

enum Buttons {
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Init font
    TTF_Font *scoreFont = TTF_OpenFont("DejaVuSansMono.ttf", 40);

    // Create player score text
    PlayerScore player1Score(Vec2(WINDOW_WIDTH / 4, 20), renderer, scoreFont);
    PlayerScore player2Score(Vec2((3 * WINDOW_WIDTH) / 4, 20), renderer, scoreFont);

    // Create ball
    Ball ball(Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)));

    // Create paddles, with start speed 0
    Paddle paddle1(Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)),
                   Vec2(0.0f, 0.0f));
    Paddle paddle2(Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)),
                   Vec2(0.0f, 0.0f));

    bool running = true;
    bool buttons[4] = {};

    float dt = 0.0f;

    while (running) {

        auto startTime = std::chrono::high_resolution_clock::now();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN) {          // On key press
                if (event.key.keysym.sym == SDLK_ESCAPE) { // Escape character pressed, close game
                    running = false;
                    // Move paddles using w,s,up,down
                } else if (event.key.keysym.sym == SDLK_w) {
                    buttons[Buttons::PaddleOneUp] = true;
                } else if (event.key.keysym.sym == SDLK_s) {
                    buttons[Buttons::PaddleOneDown] = true;
                } else if (event.key.keysym.sym == SDLK_UP) {
                    buttons[Buttons::PaddleTwoUp] = true;
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    buttons[Buttons::PaddleTwoDown] = true;
                }
            } else if (event.type == SDL_KEYUP) { // On letting go of key
                if (event.key.keysym.sym == SDLK_w) {
                    buttons[Buttons::PaddleOneUp] = false;
                } else if (event.key.keysym.sym == SDLK_s) {
                    buttons[Buttons::PaddleOneDown] = false;
                } else if (event.key.keysym.sym == SDLK_UP) {
                    buttons[Buttons::PaddleTwoUp] = false;
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    buttons[Buttons::PaddleTwoDown] = false;
                }
            }
        }

        // Actually react to button press
        // Player 1
        if (buttons[Buttons::PaddleOneUp]) {
            paddle1.velocity_.y_ = -PADDLE_SPEED;
        } else if (buttons[Buttons::PaddleOneDown]) {
            paddle1.velocity_.y_ = PADDLE_SPEED;
        } else {
            paddle1.velocity_.y_ = 0.0f;
        }
        // Player 2
        if (buttons[Buttons::PaddleTwoUp]) {
            paddle2.velocity_.y_ = -PADDLE_SPEED;
        } else if (buttons[Buttons::PaddleTwoDown]) {
            paddle2.velocity_.y_ = PADDLE_SPEED;
        } else {
            paddle2.velocity_.y_ = 0.0f;
        }

        paddle1.Update(dt);
        paddle2.Update(dt);

        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (int i = 0; i < WINDOW_HEIGHT; i++) {
            if (i % 5)
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, i);
        }

        ball.Draw(renderer); // Draw ball

        paddle1.Draw(renderer); // Draw paddles
        paddle2.Draw(renderer);

        player1Score.Draw(); // Draw scores
        player2Score.Draw();

        SDL_RenderPresent(renderer); // Present backbuffer

        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }

    // Cleanup

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scoreFont);
    TTF_Quit();
    SDL_Quit();

    return 0;
}