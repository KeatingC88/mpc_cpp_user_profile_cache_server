cmake_minimum_required(VERSION 3.16)
project(mpc_cpp_user_profile_cache_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define ASIO_STANDALONE globally
add_definitions(-DASIO_STANDALONE)

set(TACOPIE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tacopie/includes")
set(TACOPIE_LIBRARY tacopie)

add_definitions(-D_WIN32_WINNT=0x0601)
find_package(OpenSSL REQUIRED)

# Add subdirectories
add_subdirectory(jwt-cpp)

add_subdirectory(tacopie)

add_subdirectory(cpp_redis)

# Include headers
include_directories(
    ${CMAKE_SOURCE_DIR}/crow/include
    ${CMAKE_SOURCE_DIR}/asio/asio/include
    ${CMAKE_SOURCE_DIR}/cpp_redis/includes
    ${CMAKE_SOURCE_DIR}/tacopie/includes
    ${CMAKE_SOURCE_DIR}/jwt-cpp/include
    ${CMAKE_SOURCE_DIR}/nlohmann/include
)

# Define the executable
add_executable(mpc_cpp_user_profile_cache_server mpc_cpp_user_profile_cache_server.cpp)

# Link libraries
target_link_libraries(mpc_cpp_user_profile_cache_server
    PRIVATE 
    OpenSSL::Crypto
    cpp_redis
    tacopie
)