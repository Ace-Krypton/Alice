/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <iomanip>
#include <iostream>
#include <openssl/rand.h>

#include "encryption/encryptor.hpp"
#include "decryption/decryptor.hpp"

auto main() -> std::int32_t {
    const unsigned char key[] = {
            0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
            0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
            0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
            0x79, 0x7a, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
    };

    [[maybe_unused]] const int KEY_SIZE = sizeof(key);
    const char* in_file = "/home/draco/tobe_encrypted.txt";
    const char* encr_out_file = "/home/draco/encrypted_output.txt";

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

    int encrypted_bytes_written = Encryptor::encrypt(in_file, encr_out_file, key, iv);
    if (encrypted_bytes_written > 0) {
        std::cout << "File encrypted successfully. " << encrypted_bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "Error encrypting file" << std::endl;
    }

    unsigned char _iv[EVP_MAX_IV_LENGTH] = {
            0x5c, 0x52, 0x19, 0x84, 0xa3, 0xdd, 0xe9, 0x1a,
            0x80, 0x89, 0xf0, 0x8d, 0x45, 0xf2, 0xef, 0xbf
    };
    const char* decr_out_file = "/home/draco/decrypted_output.txt";
    int decrypted_bytes_written = Decryptor::decrypt(encr_out_file, decr_out_file, key, _iv);
    if (decrypted_bytes_written > 0) {
        std::cout << "File decrypted successfully. " << decrypted_bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "Error decrypting file" << std::endl;
    }

    return 0;
}
