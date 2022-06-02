#include "Client.hpp"

Client::Client(PlayerState& player, std::string_view host, std::string_view port)
    : m_player(player), m_socket(m_context) {

}