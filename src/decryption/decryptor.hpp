/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#ifndef CORPSE_DECRYPTOR_HPP
#define CORPSE_DECRYPTOR_HPP

struct Decryptor {
    auto static decrypt(const char* in_file,
                        const char* out_file,
                        const unsigned char* key,
                        const unsigned char* iv) -> int;
};

#endif //CORPSE_DECRYPTOR_HPP
