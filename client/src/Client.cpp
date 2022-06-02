#include "Client.hpp"

#include <memory>

Client::Client(Player& player, std::string_view host, std::string_view port)
    : m_player(player), m_socket(m_context) {
    m_id = UINT32_MAX;

    boost::asio::ip::udp::resolver resolver(m_context);
    m_endpoint = *resolver.resolve(boost::asio::ip::udp::v4(), host, port);

    m_socket.open(boost::asio::ip::udp::v4());

    do_receive();
}

void Client::run() {
    m_context.run();
}

void Client::do_send(ClientPayload& payload) {
    payload.id = m_id;
    auto buffer = std::make_shared<ClientPayload::Buffer>(payload.encode());
    m_socket.async_send_to(boost::asio::buffer(*buffer), m_endpoint,
        [buffer](const boost::system::error_code&, std::size_t) {

        });
}

void Client::do_receive() {
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_endpoint, 
        [this](const boost::system::error_code& error, std::size_t size) {
            if (!error && size == ServerPayload::size) {
                ServerPayload payload;
                payload.decode(m_buffer);

                if (m_id == UINT32_MAX) {
                    m_id = payload.id;
                }

                m_player.setPosition(payload.x, payload.y);
            } else {
                do_receive();
            }
        });
}