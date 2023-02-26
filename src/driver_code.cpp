/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <iomanip>
#include <fstream>
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

    std::ofstream iv_writer("/home/draco/IV.txt");
    for (unsigned char i : iv) {
        iv_writer << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
        iv_writer << '\n';
    }
    iv_writer.close();

    int encrypted_bytes_written = Encryptor::encrypt(in_file, encr_out_file, key, iv);
    if (encrypted_bytes_written > 0) {
        std::cout << "File encrypted successfully. " << encrypted_bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "Error encrypting file" << std::endl;
    }

    unsigned char _iv[EVP_MAX_IV_LENGTH];
    std::ifstream iv_reader("/home/draco/IV.txt");

    for (unsigned char &element : _iv) {
        std::string hex_byte;
        if (!getline(iv_reader, hex_byte)) {
            std::cerr << "Error reading IV from file" << std::endl;
            return -1;
        }
        element = static_cast<unsigned char>(std::stoi(hex_byte, nullptr, 16));
    }
    iv_reader.close();

    const char* decr_out_file = "/home/draco/decrypted_output.txt";
    int decrypted_bytes_written = Decryptor::decrypt(encr_out_file, decr_out_file, key, _iv);
    if (decrypted_bytes_written > 0) {
        std::cout << "File decrypted successfully. " << decrypted_bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "Error decrypting file" << std::endl;
    }

    return 0;
}