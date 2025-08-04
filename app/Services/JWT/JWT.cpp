#include <iostream>
#include "jwt-cpp/jwt.h"
#include <json.hpp>
#include "JWT.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "../AES/AES.h"
#include "../ENV/ENV.h"

using json = nlohmann::json;

namespace App::Services::JWT {

    App::Services::AES::AES AES;
    App::Services::ENV::ENV ENV;

    JWT::JWT() {}

    bool JWT::Authenticate_Claims(std::string JWT) const {
        try {
            std::string JWT_ISSUER_KEY = ENV.Read("JWT_ISSUER_KEY");
            std::string JWT_CLIENT_KEY = ENV.Read("JWT_CLIENT_KEY");
            std::string JWT_CLIENT_ADDRESS = ENV.Read("JWT_CLIENT_ADDRESS");

            auto decoded = jwt::decode(JWT);
            auto payload_json = nlohmann::json::parse(decoded.get_payload());

            for (auto it = payload_json.begin(); it != payload_json.end(); ++it) {
                if (it.value().is_string()) {

                    
                    if (it.key() == "aud" && AES.Decrypt(it.value()) != JWT_CLIENT_KEY) {
                        return false;
                    } else if (it.key() == "iss" && AES.Decrypt(it.value()) != JWT_ISSUER_KEY) {
                        return false;
                    } else if (AES.Decrypt(it.value()) != JWT_CLIENT_ADDRESS) {
                        return true;
                    }

                } else if (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) >= it.value()) {
                    return false;
                }
            }
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }
}