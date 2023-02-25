/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#ifndef CORPSE_ENCRYPTOR_HPP
#define CORPSE_ENCRYPTOR_HPP

struct Encryptor {
    auto static encrypt(const char* in_file, const char* out_file, const unsigned char* key, const unsigned char* iv) -> int;
};

#endif //CORPSE_ENCRYPTOR_HPP
