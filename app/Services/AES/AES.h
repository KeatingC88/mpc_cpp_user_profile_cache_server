#ifndef AES_H
#define AES_H

#include <string>

namespace App::Services::AES {
    class AES {

    public:
        AES();
        std::string Decrypt(const std::string& encrypted_string) const;
        std::string Encrypt(const std::string& plain_text) const;
    private:
        std::string encrypted_string;
    };
}

#endif
