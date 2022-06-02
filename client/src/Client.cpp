#include "Client.hpp"

#include <memory>

Client::Client(PlayerState& player, std::string_view host, std::string_view port)
    : m_player(player), m_socket(m_context) {
    boost::asio::ip::udp::resolver resolver(m_context);
    m_endpoint = *resolver.resolve(boost::asio::ip::udp::v4(), host, port);

    m_socket.open(boost::asio::ip::udp::v4());

    do_receive();
}

void Client::run() {
    m_context.run();
}

void Client::do_send() {
    auto buffer = std::make_shared<std::array<uint8_t, PLAYER_PACKET_SIZE>>(m_player.serialize());
    m_socket.async_send_to(boost::asio::buffer(*buffer), m_endpoint,
        [buffer](const boost::system::error_code&, std::size_t) {

        });
}

void Client::do_receive() {
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_endpoint, 
        [this](const boost::system::error_code& error, std::size_t) {
            if (!error) {
                m_player.deserialize(m_buffer);
            } else {
                do_receive();
            }
        });
}