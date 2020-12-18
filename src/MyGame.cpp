#include "MyGame.h"

MyGame::MyGame(TTF_Font* font) {
    this->font = font;
}
void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } 
    
    // new command
    
    else {
        std::cout << "Received: " << cmd << std::endl;

        if (cmd == "HIT_WALL_RIGHTGAME_DATA") {
            game_data.scoreOne++;
            std::cout << "Player one has a score of " << game_data.scoreOne << std::endl;
        }
        else if (cmd == "HIT_WALL_LEFTGAME_DATA") {
            game_data.scoreTwo++;
            std::cout << "Player two has a score of " << game_data.scoreTwo << std::endl;
        }
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;

        case SDLK_i:
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            break;
        case SDLK_k:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            break;

    }
}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;
    ball.x = game_data.ballX;
    ball.y = game_data.ballY;
}

void MyGame::render(SDL_Renderer* renderer) {


    SDL_Color blue_colour = { 87, 110, 224, 0 };
    SDL_Color red_colour = { 224, 87, 87, 0};

    std::string scoreOne_text = std::to_string(game_data.scoreOne);
    std::string scoreTwo_text = std::to_string(game_data.scoreTwo);

    SDL_Surface* text_surface_blue = TTF_RenderText_Blended(font, scoreOne_text.c_str(), blue_colour);
    
    if (text_surface_blue != nullptr) {
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface_blue);
        SDL_FreeSurface(text_surface_blue);

        if (text_texture != nullptr) {
            int w, h;
            SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);
            SDL_Rect dst = { 350, 50, w, h };
            SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        }
    }

    SDL_Surface* text_surface_red = TTF_RenderText_Blended(font, scoreTwo_text.c_str(), red_colour);

    if (text_surface_red != nullptr) {
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface_red);
        SDL_FreeSurface(text_surface_red);

        if (text_texture != nullptr) {
            int w, h;
            SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);
            SDL_Rect dst = { 450, 50, w, h };
            SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        }
    }

    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);

    SDL_RenderDrawRect(renderer, &ball);
}