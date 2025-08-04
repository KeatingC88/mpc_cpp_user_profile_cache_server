#include <iostream>
#include "jwt-cpp/jwt.h"
#include <json.hpp>
using json = nlohmann::json;
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "../JWT/JWT.h"
#include "../ENV/ENV.h"
#include "../AES/AES.h"

namespace App::Services::AES {

    App::Services::ENV::ENV ENV;
    std::string key_str = ENV.Read("ENCRYPTION_KEY");
    std::string iv_str = ENV.Read("ENCRYPTION_IV");

    AES::AES() {
        if (key_str.length() != 32 || iv_str.length() != 16) {
            std::cerr << "Invalid key or IV length in environment variables." << std::endl;
        }

        std::cout << "Encryption loaded successfully.\n";
    }

    std::vector<unsigned char> Base64_Decoder(const std::string& input) {
        BIO* bio = BIO_new_mem_buf(input.data(), input.length());
        BIO* b64 = BIO_new(BIO_f_base64());
        bio = BIO_push(b64, bio);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

        std::vector<unsigned char> output(input.length());
        int len = BIO_read(bio, output.data(), static_cast<int>(input.length()));
        output.resize(len > 0 ? len : 0);

        BIO_free_all(bio);
        return output;
    }

    std::vector<unsigned char> SHA256(const std::string& input) {
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
        ::SHA256(reinterpret_cast<const unsigned char*>(input.data()), input.size(), hash.data());
        return hash;
    }

    std::vector<unsigned char> global_key = SHA256(key_str);
    std::vector<unsigned char> global_iv = std::vector<unsigned char>(iv_str.begin(), iv_str.end());

    std::string AES::Decrypt(const std::string& base64_ciphertext) const {

        std::vector<unsigned char> ciphertext = Base64_Decoder(base64_ciphertext);
        std::vector<unsigned char> plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) throw std::runtime_error("Failed to create context");

        int len = 0, plaintext_len = 0;

        if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, global_key.data(), global_iv.data()))
            throw std::runtime_error("DecryptInit failed");

        if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()))
            throw std::runtime_error("DecryptUpdate failed");

        plaintext_len = len;

        if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
            throw std::runtime_error("DecryptFinal failed");

        plaintext_len += len;
        plaintext.resize(plaintext_len);
        EVP_CIPHER_CTX_free(ctx);

        return std::string(plaintext.begin(), plaintext.end());
    }
}