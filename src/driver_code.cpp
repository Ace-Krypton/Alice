/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <random>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <openssl/rand.h>

#include "encryption/encryptor.hpp"
#include "decryption/decryptor.hpp"

auto main_menu() -> void {
    std::cout << "[1] Encrypt the file" << std::endl;
    std::cout << "[2] Decrypt the file\n" << std::endl;
    std::cout << "[0] Exit" << std::endl;
}

auto test_encrypt(const char* in_file, const char* encr_out_file, const unsigned char key[]) -> std::int32_t {
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
        std::cout << "File encrypted successfully. " << encrypted_bytes_written << " bytes written.\n" << std::endl;
    } else {
        std::cerr << "Error encrypting file" << std::endl;
    }

    return 0;
}

auto test_decrypt(const char* encr_out_file, const unsigned char key[]) -> std::int32_t {
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

auto main() -> std::int32_t {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uint_fast8_t _key[32];
    std::uniform_int_distribution<std::uint_fast8_t> keys(0, 32);

    for (std::uint_fast8_t &randoms : _key) {
        randoms = keys(engine);
    }

    for (std::uint_fast8_t rolls = 0; rolls < 32; rolls++) {
        if (rolls % 8 == 0) std::cout << "\n    ";
        std::cout << "0x" << std::hex << (int)_key[rolls];
        if (rolls != 31) std::cout << ",";
        std::cout << " ";
    }

    const std::uint_fast8_t key[32] = {
            0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
            0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
            0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
            0x79, 0x7a, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
    };

    [[maybe_unused]] const int KEY_SIZE = sizeof(key);
    const char* in_file = "/home/draco/tobe_encrypted.txt";
    const char* encr_out_file = "/home/draco/encrypted_output.txt";

    int input;
    bool main_loop = true;

    while (main_loop) {
        main_menu();
        std::cout << "\n> ";
        std::cin >> input;

        switch (input) {
            case 1:
                test_encrypt(in_file, encr_out_file, key);
                break;
            case 2:
                test_decrypt(encr_out_file, key);
                break;
            case 0:
                main_loop = false;
                break;
            default:
                std::cout << "[-] Invalid command, Please try again" << std::endl;
        }
    }

    return 0;
}
