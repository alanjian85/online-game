#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string_view>

#include <boost/asio.hpp>

#include "PlayerState.hpp"

class Client {
public:
    Client(PlayerState& player, std::string_view host, std::string_view port);
private:
    PlayerState& m_player;

    boost::asio::io_context m_context;
    boost::asio::ip::udp::socket m_socket;
};

#endif