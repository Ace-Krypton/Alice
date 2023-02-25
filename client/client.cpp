/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <string>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>

#include "client.hpp"

auto ClientSide::connection(const std::string& message) -> std::int32_t {
    std::string host = "localhost";
    std::string port = "3169";

    addrinfo hints { };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* server_address;
    std::int32_t status = getaddrinfo(host.c_str(),
                             port.c_str(),
                             &hints,
                             &server_address);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return -1;
    }

    std::int32_t client_socket = socket(server_address->ai_family,
                               server_address->ai_socktype,
                               server_address->ai_protocol);

    if (client_socket == -1) {
        std::cerr << "Cannot create socket" << std::endl;
        return -2;
    }

    if (connect(client_socket, server_address->ai_addr,server_address->ai_addrlen) == -1) {
        std::cerr << "Cannot connect to server" << std::endl;
        close(client_socket);
        return -3;
    }

    freeaddrinfo(server_address);

    ssize_t sent = send(client_socket, message.c_str(), message.size() + 1, 0);

    if (sent == -1) {
        std::cerr << "Cannot send message" << std::endl;
        close(client_socket);
        return -4;
    }

    char buffer[4096];
    std::memset(buffer, 0, 4096);

    ssize_t received = recv(client_socket, buffer, 4096, 0);

    if (received == -1) {
        std::cerr << "There was a connection issue" << std::endl;
        close(client_socket);
        return -5;
    }

    std::cout << "Received: " << std::string(buffer, received) << std::endl;

    close(client_socket);
}
