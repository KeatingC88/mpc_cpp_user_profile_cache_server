#ifndef JWT_H
#define JWT_H

#include <string>

namespace App::Services::JWT {
    class JWT {
    public:
        JWT();
        bool Authenticate_Claims(std::string jwt) const;
    };
}

#endif
