cmake_minimum_required(VERSION 3.10)

project(TCPServerClient)

set(CMAKE_CXX_STANDARD 11)

# Додати шляхи до заголовкових файлів
include_directories(src)

# Збірка сервера
add_executable(server src/main.cpp src/tcpServer.cpp)

# Збірка клієнта
add_executable(client src/tcpClient.cpp)
