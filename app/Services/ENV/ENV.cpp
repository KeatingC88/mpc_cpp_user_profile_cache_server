#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "ENV.h"

namespace App::Services::ENV {

    ENV::ENV() {}

    void ENV::Load_Env_File() const {

        std::ifstream file(".env");

        if (!file.is_open()) {
            std::cerr << "Could not open .env file\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::istringstream lineStream(line);
            std::string key, value;

            if (std::getline(lineStream, key, '=') &&
                std::getline(lineStream, value)) {

                if (!value.empty() && value.back() == '\r') {
                    value.pop_back();
                }

                #ifdef _WIN32
                _putenv_s(key.c_str(), value.c_str());
                #else
                setenv(key.c_str(), value.c_str(), 1);
                #endif
            }
        }

    }

    std::string ENV::Read(const char* key) const {
        const char* val = std::getenv(key);
        if (!val) {
            throw std::runtime_error(std::string("Missing required env variable: ") + key);
        }
        return std::string(val);
    }
}
