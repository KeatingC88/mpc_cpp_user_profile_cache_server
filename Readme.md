# Cmake Build Instructions (preferred method)
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release

# Docker Option 1) for CLI command:
1) Navigate CLI to folder and use
docker compose -f mpc_cpp_user_profile_cache_server.yaml up -d

# Docker Option 2) startup for CLI command:
1) Navigate CLI to folder and use
docker build -t mpc_cpp_online_status_server_rom .
docker run -d -p {SERVER_NETWORK_PORT_NUMBER}:{DOCKER_CONTAINER_PORT_NUMBER} --name mpc_cpp_user_profile_cache_server mpc_cpp_online_status_server_rom

# Other Notes
.Env file must be in the same directory as the .exe inside the build folder.

# Dependencies that you must have somewhere in your project
Library	Repo URL
Crow	https://github.com/CrowCpp/crow.git
ASIO	https://github.com/chriskohlhoff/asio.git
tacopie	https://github.com/Cylix/tacopie.git
cpp_redis	https://github.com/Cylix/cpp_redis.git
jwt-cpp	https://github.com/Thalhammer/jwt-cpp.git
nlohmann	https://github.com/nlohmann/json.git


# Example .Env File you must create and adjust outside of Docker
HOST_IP_ADDRESS=127.0.0.1 
HOST_PORT_ADDRESS=8000
REDIS_HOST_ADDRESS=127.0.0.1
REDIS_PORT_ADDRESS=6379

ENCRYPTION_KEY=(enter 32 character string here
ENCRYPTION_IV=(enter 16 character string here)

JWT_ISSUER_KEY=(Only use if ur encrpting values)
JWT_CLIENT_KEY=(you may have to modify the code to remove these)

# Example .Env File you must create and adjust inside of Docker
HOST_IP_ADDRESS=(container_name)
HOST_PORT_ADDRESS=(container_port)
REDIS_HOST_ADDRESS=(redis_container_name)
REDIS_PORT_ADDRESS=6379

ENCRYPTION_KEY=(enter 32 character string here)
ENCRYPTION_IV=(enter 16 character string here)

JWT_ISSUER_KEY=(Only use if ur encrpting values)
JWT_CLIENT_KEY=(you may have to modify the code to remove these)

# Cmakeuplist.txt of what's in here
cmake_minimum_required(VERSION 3.16)
project(mpc_cpp_user_profile_cache_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DASIO_STANDALONE)

set(TACOPIE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tacopie/includes")
set(TACOPIE_LIBRARY tacopie)

add_definitions(-D_WIN32_WINNT=0x0601)
find_package(OpenSSL REQUIRED)


add_subdirectory(jwt-cpp)

add_subdirectory(tacopie)

add_subdirectory(cpp_redis)

include_directories(
    ${CMAKE_SOURCE_DIR}/crow/include
    ${CMAKE_SOURCE_DIR}/asio/asio/include
    ${CMAKE_SOURCE_DIR}/cpp_redis/includes
    ${CMAKE_SOURCE_DIR}/tacopie/includes
    ${CMAKE_SOURCE_DIR}/jwt-cpp/include
    ${CMAKE_SOURCE_DIR}/nlohmann/include
)

add_executable(mpc_cpp_user_profile_cache_server mpc_cpp_user_profile_cache_server.cpp)

target_link_libraries(mpc_cpp_user_profile_cache_server
    PRIVATE 
    OpenSSL::Crypto
    cpp_redis
    tacopie
)

# Example POST - SET example

{
  "id": "Base64EncryptedUserId",
  "online_status": "Base64EncryptedStatus",
  "token": "JWTToken"
}

# Example POST - GET example by ID
{
  "id": "Base64EncryptedUserId",
  "token": "JWTToken"
}

# Example POST - GET_ALL example for all users
{
  "token": "JWTToken"
}

