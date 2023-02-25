/*
 * (C)opyright 2022 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#pragma once
#ifndef CLIENT_SIDE_CONNECTION_HPP
#define CLIENT_SIDE_CONNECTION_HPP

struct ClientSide {
    auto static connection(const std::string& message) -> int;
};

#endif //CLIENT_SIDE_CONNECTION_HPP
