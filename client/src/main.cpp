#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

#include <boost/asio.hpp>
#include "SDL.h"

#include "constants.hpp"
#include "PlayerState.hpp"
#include "Client.hpp"

namespace asio = boost::asio;
using asio::ip::udp;

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            throw std::invalid_argument("Usage: client <host> <port>");
        }
    
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(
            "Online Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, 0
        );
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

        PlayerState player;
        player.x = PLAYER_SPAWN_X;
        player.y = PLAYER_SPAWN_Y;
        player.id = UINT32_MAX;

        bool quit = false;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                }
            }

            const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
            player.forward  = keyboardState[SDL_SCANCODE_W];
            player.backward = keyboardState[SDL_SCANCODE_S];
            player.left     = keyboardState[SDL_SCANCODE_A];
            player.right    = keyboardState[SDL_SCANCODE_D];

            auto buffer = player.serialize();
            //socket.send_to(asio::buffer(buffer), endpoint);

            SDL_SetRenderDrawColor(renderer, 235, 64, 52, 255);
            SDL_RenderClear(renderer);

            SDL_Rect rect;
            rect.x = player.x;
            rect.y = player.y;
            rect.w = 50;
            rect.h = 50;
            SDL_SetRenderDrawColor(renderer, 252, 186, 3, 255);
            SDL_RenderFillRect(renderer, &rect);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}