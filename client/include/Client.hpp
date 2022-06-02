#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string_view>
#include <array>

#include <boost/asio.hpp>

#include "ClientPayload.hpp"
#include "ServerPayload.hpp"
#include "Player.hpp"

class Client {
public:
    Client(Player& player, std::string_view host, std::string_view port);

    void run();

    void do_send(ClientPayload& payload);
private:
    void do_receive();

private:
    uint32_t m_id;
    Player& m_player;

    boost::asio::io_context m_context;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_endpoint;

    ServerPayload::Buffer m_buffer;
};

#endif