#include "tcpServer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>

// Глобальні змінні для роботи з потоками і логуванням
std::vector<std::thread> threads;
std::mutex logMutex;
std::ofstream logFile("server.log", std::ios::app);

TCPServer::TCPServer(const std::string &address, int port)
    : address(address), port(port) {}

// Функція для логування повідомлень
void logMessage(const std::string &message) {
    std::lock_guard<std::mutex> lock(logMutex);
    logFile << message << std::endl;
}

// Обробка клієнта у окремому потоці
void handleClient(int clientSocket) {
    char buffer[1024];
    const char *welcomeMessage = "Welcome to the server!";
    send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead <= 0) break; // Клієнт відключився або виникла помилка

        // Логування отриманого повідомлення
        std::string logEntry = "Client: " + std::string(buffer);
        logMessage(logEntry);

        // Відправка відповіді клієнту
        std::string response = "Echo: " + std::string(buffer);
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket); // Закриваємо сокет клієнта
}

void TCPServer::start() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Створення сокета
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return;
    }

    // Налаштування адреси сервера
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Прив'язка сокета до порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return;
    }

    // Переведення сервера у режим прослуховування
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return;
    }

    std::cout << "Server listening on " << this->address << ":" << this->port << std::endl;

    // Цикл прийому клієнтів
    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Запуск нового потоку для кожного клієнта
        threads.emplace_back(handleClient, new_socket);
    }

    // Очікування завершення всіх потоків
    for (auto &t : threads) {
        if (t.joinable()) t.join();
    }

    close(server_fd); // Закриття серверного сокета
}
