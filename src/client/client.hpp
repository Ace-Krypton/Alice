/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#pragma once
#ifndef CLIENT_SIDE_CONNECTION_HPP
#define CLIENT_SIDE_CONNECTION_HPP

struct [[maybe_unused]] ClientSide {
    [[maybe_unused]] auto static connection(const std::string& message) -> int;
};

#endif //CLIENT_SIDE_CONNECTION_HPP
