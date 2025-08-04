#pragma once

#include "../../crow/include/crow_all.h"
#include "../Services/CORS/CORS.h" 

namespace App::Controllers {
    class Users_Profile_Controller {
    public:
        static void RegisterRoutes(crow::App<CORS>& app);
    };
}
