#ifndef AES_H
#define AES_H

#include <string>

namespace App::Services::AES {
    class AES {
    public:
        AES();
        std::string Decrypt(const std::string& encrypted_string) const;
    private:
        std::string encrypted_string;
    };
}

#endif
