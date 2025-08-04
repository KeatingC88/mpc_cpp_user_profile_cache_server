
#include "crow_all.h"

#include "app/Services/ENV/ENV.h"
#include "app/Services/AES/AES.h"
#include "app/Services/JWT/JWT.h"
#include "app/Controllers/Users_Profile_Controller.h"
#include "app/Services/CORS/CORS.h" 

crow::SimpleApp app;

int main()
{
    crow::App<CORS> app;
    App::Services::AES::AES AES;
    App::Services::JWT::JWT JWT;
    App::Services::ENV::ENV ENV;

    ENV.Load_Env_File();

    try {

        std::string SERVER_NETWORK_HOST_IP = ENV.Read("SERVER_NETWORK_HOST_IP");
        std::string SERVER_NETWORK_SOCKET_PORT = ENV.Read("SERVER_NETWORK_SOCKET_PORT");

        App::Controllers::Users_Profile_Controller::RegisterRoutes(app);

        app.bindaddr(SERVER_NETWORK_HOST_IP).port(std::stoi(SERVER_NETWORK_SOCKET_PORT)).multithreaded().run();

        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 0;
    }
}