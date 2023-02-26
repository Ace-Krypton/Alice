/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <fstream>
#include <iostream>
#include <openssl/evp.h>

#include "encryptor.hpp"

auto Encryptor::encrypt(const char* in_file,
                        const char* out_file,
                        const unsigned char* key,
                        const unsigned char* iv) -> int {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        std::cerr << "Error creating cipher context" << std::endl;
        return -1;
    }

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), nullptr, key, iv)) {
        std::cerr << "Error initializing cipher" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    std::ifstream infile(in_file, std::ios::binary);
    std::ofstream outfile(out_file, std::ios::binary);
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error opening files" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        infile.close();
        outfile.close();
        return -1;
    }

    const int BLOCK_SIZE = 1024;
    unsigned char in_buff[BLOCK_SIZE];
    unsigned char out_buff[BLOCK_SIZE + EVP_MAX_BLOCK_LENGTH];
    int num_bytes_read, out_len = 0, total_out_len = 0;

    while ((num_bytes_read = static_cast<int>(infile.read((char*)in_buff, BLOCK_SIZE).gcount())) > 0) {
        if (!EVP_EncryptUpdate(ctx, out_buff, &out_len, in_buff, num_bytes_read)) {
            std::cerr << "Error encrypting data" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            infile.close();
            outfile.close();
            return -1;
        }
        outfile.write((char*)out_buff, out_len);
        total_out_len += out_len;
    }

    if (!EVP_EncryptFinal_ex(ctx, out_buff, &out_len)) {
        std::cerr << "Error finalizing cipher" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        infile.close();
        outfile.close();
        return -1;
    }
    outfile.write((char*)out_buff, out_len);
    total_out_len += out_len;

    infile.close();
    outfile.close();
    EVP_CIPHER_CTX_free(ctx);

    return total_out_len;
}
