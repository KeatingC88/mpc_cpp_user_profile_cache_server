#ifndef ENV_H
#define ENV_H

namespace App::Services::ENV {

    class ENV {

    public:
        ENV();
        void Load_Env_File() const;
        std::string Read(const char* key) const;

    };
}

#endif