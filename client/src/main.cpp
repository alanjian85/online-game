#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include <boost/asio.hpp>

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
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}