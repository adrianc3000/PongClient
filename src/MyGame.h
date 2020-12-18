#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL_ttf.h"
#include "SDL.h"

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
    int scoreOne = 0;
    int scoreTwo = 0;
} game_data;

class Bat {

};

class Ball {
    //SDL_Rect ball = { 0, 0, 20, 20 };
};

class MyGame {

    private:
        SDL_Rect player1 = { 200, 0, 20, 60 };
        SDL_Rect player2 = { 580, 0, 20, 60 };
        SDL_Rect ball = { 0, 0, 20, 20 };
        
        TTF_Font* font;

    public:
        MyGame(TTF_Font* font);
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif