#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <vector>
#include <thread>   // Для роботи з потоками
#include <mutex>    // Для захисту доступу до лог-файлу
#include <fstream>  // Для логування

class TCPServer {
public:
    TCPServer(const std::string &address, int port);
    void start();

private:
    std::string address;
    int port;
    std::vector<std::thread> threads;   // Потоки для обробки клієнтів
    std::mutex logMutex;  // Мьютекс для логування
    std::ofstream logFile; // Лог-файл

    // Метод для логування повідомлень
    void logMessage(const std::string &message);

    // Метод для обробки клієнтів
    void handleClient(int clientSocket);
};

#endif // TCPSERVER_H
