#include "MyGame.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

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
            game_info.scoreOne++;
            std::cout << "Player one has a score of " << game_info.scoreOne << std::endl;
        }
        else if (cmd == "HIT_WALL_LEFTGAME_DATA") {
            game_info.scoreTwo++;
            std::cout << "Player two has a score of " << game_info.scoreTwo << std::endl;
        }
        else if (cmd == "BALL_HIT_BAT1" || cmd == "BALL_HIT_BAT2" || cmd == "HIT_WALL_DOWN" || cmd == "HIT_WALL_UP") {
            Mix_Chunk* sound = Mix_LoadWAV("assets/explosion.wav");
            if (Mix_PlayChannel(-1, sound, 0) == -1) {
                printf("Mix_PlayChannel: %s \n", Mix_GetError());
            }
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

    std::string scoreOne_text = std::to_string(game_info.scoreOne);
    std::string scoreTwo_text = std::to_string(game_info.scoreTwo);

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
        SDL_DestroyTexture(text_texture);
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
        SDL_DestroyTexture(text_texture);
    }

    SDL_RenderDrawRect(renderer, &ball);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int ball_width = 50;
    int ball_height = 50;

    SDL_Rect drawBall = { game_data.ballX - 17.5, game_data.ballY - 17.5, ball_width, ball_height };
    auto imgBall = IMG_Load("assets/ball.png");
    auto textureBall = SDL_CreateTextureFromSurface(renderer, imgBall);
    SDL_RenderCopy(renderer, textureBall, NULL, &drawBall);

    int bat_width = 20;
    int bat_height = 60;

    SDL_Rect drawP1 = { 200, game_data.player1Y, bat_width, bat_height };
    auto imgP1 = IMG_Load("assets/blue.png");
    auto textureP1 = SDL_CreateTextureFromSurface(renderer, imgP1);
    SDL_RenderCopy(renderer, textureP1, NULL, &drawP1);


    SDL_Rect drawP2 = { 580, game_data.player2Y, bat_width, bat_height };
    auto imgP2 = IMG_Load("assets/red.png");
    auto textureP2 = SDL_CreateTextureFromSurface(renderer, imgP2);
    SDL_RenderCopy(renderer, textureP2, NULL, &drawP2);

    SDL_RenderPresent(renderer);
    SDL_FreeSurface(imgBall);
    SDL_FreeSurface(imgP1);
    SDL_FreeSurface(imgP2);
    SDL_DestroyTexture(textureBall);
    SDL_DestroyTexture(textureP1);
    SDL_DestroyTexture(textureP2);
}