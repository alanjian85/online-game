#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string_view>
#include <array>

#include <boost/asio.hpp>

#include "PlayerState.hpp"

class Client {
public:
    Client(PlayerState& player, std::string_view host, std::string_view port);

    void run();

    void do_send();
private:
    void do_receive();

private:
    PlayerState& m_player;

    boost::asio::io_context m_context;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_endpoint;

    std::array<char, PLAYER_PACKET_SIZE> m_buffer;
};

#endif