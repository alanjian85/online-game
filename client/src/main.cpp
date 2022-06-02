#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cassert>
#include <thread>

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

        PlayerState player;
        Client client(player, argv[1], argv[2]);
        std::thread clientThread([&client]() { client.run(); });
    
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(
            "Online Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, 0
        );
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

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
            player.setForward(keyboardState[SDL_SCANCODE_W]);
            player.setBackward(keyboardState[SDL_SCANCODE_S]);
            player.setLeft(keyboardState[SDL_SCANCODE_A]);
            player.setRight(keyboardState[SDL_SCANCODE_D]);

            client.do_send();

            SDL_SetRenderDrawColor(renderer, 235, 64, 52, 255);
            SDL_RenderClear(renderer);

            SDL_Rect rect;
            rect.x = player.getX();
            rect.y = player.getY();
            rect.w = 50;
            rect.h = 50;
            SDL_SetRenderDrawColor(renderer, 252, 186, 3, 255);
            SDL_RenderFillRect(renderer, &rect);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        clientThread.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}