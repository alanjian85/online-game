#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cassert>
#include <thread>

#include <boost/asio.hpp>
#include "SDL.h"

#include "Client.hpp"

namespace asio = boost::asio;
using asio::ip::udp;

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            throw std::invalid_argument("Usage: client <host> <port>");
        }

        auto player = std::make_shared<Player>();
        player->setPosition(375, 275);

        auto client = std::make_shared<Client>(*player, argv[1], argv[2]);
        std::thread clientThread([client, player]() { client->run(); });
        clientThread.detach();
    
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(
            "Online Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            800, 600, 0
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
            ClientPayload payload;
            payload.forward = keyboardState[SDL_SCANCODE_W];
            payload.backward = keyboardState[SDL_SCANCODE_S];
            payload.left = keyboardState[SDL_SCANCODE_A];
            payload.right = keyboardState[SDL_SCANCODE_D];
            client->do_send(payload);

            SDL_SetRenderDrawColor(renderer, 235, 64, 52, 255);
            SDL_RenderClear(renderer);

            SDL_Rect rect;
            player->getPosition(rect.x, rect.y);
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