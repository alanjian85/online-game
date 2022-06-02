#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include <boost/asio.hpp>
#include "SDL.h"

#include "constants.hpp"

namespace asio = boost::asio;
using asio::ip::udp;

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            throw std::invalid_argument("Usage: client <host> <port>");
        }

        asio::io_context context;

        udp::resolver resolver(context);
        udp::endpoint endpoint = *resolver.resolve(udp::v4(), argv[1], argv[2]);

        udp::socket socket(context);
        socket.open(udp::v4());
    
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
                }
            }

            SDL_SetRenderDrawColor(renderer, 235, 64, 52, 255);
            SDL_RenderClear(renderer);

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