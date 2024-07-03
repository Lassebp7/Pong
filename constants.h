#pragma once

const int PADDLE_WIDTH = 8;
const int PADDLE_HEIGHT = 100;
const float PADDLE_SPEED = 1.0f;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;
const float BALL_SPEED = 0.5f;

enum Buttons {
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};
