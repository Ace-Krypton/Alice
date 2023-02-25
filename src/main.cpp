/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <iomanip>
#include <iostream>
#include <openssl/rand.h>

#include "encryption/encryptor.hpp"

auto main() -> std::int32_t {
    const unsigned char key[] = {
            0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
            0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
            0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
            0x79, 0x7a, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
    };

    [[maybe_unused]] const int KEY_SIZE = sizeof(key);
    const char* in_file = "/home/draco/testfile.txt";
    const char* out_file = "/home/draco/output.txt";

    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (!RAND_bytes(iv, EVP_MAX_IV_LENGTH)) {
        std::cerr << "Error generating random IV" << std::endl;
        return -1;
    }

    std::cout << "IV: ";
    for (int i = 0; i < EVP_MAX_IV_LENGTH; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(iv[i]);
        if (i < EVP_MAX_IV_LENGTH - 1) {
            std::cout << ":";
        }
    }
    std::cout << std::endl;

    int bytes_written = Encryptor::encrypt(in_file, out_file, key, iv);
    if (bytes_written > 0) {
        std::cout << "File encrypted successfully. " << bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "Error encrypting file" << std::endl;
    }

    return 0;
}
