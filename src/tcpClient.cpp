#include <iostream>
#include <unistd.h>   // Для роботи з сокетами
#include <arpa/inet.h> // Для роботи з IP-адресами
#include <string.h>    // Для роботи з низькорівневими функціями

int main() {
    const char* server_ip = "127.0.0.1";  // Локальний сервер
    int server_port = 5000;  // Порт сервера

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket!" << std::endl;
        return 1;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection failed! Error code: " << errno << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Connected to server!" << std::endl;

    const char* message = "Hello from client!";
    if (send(sock, message, strlen(message), 0) < 0) {
        std::cerr << "Send failed!" << std::endl;
    } else {
        std::cout << "Message sent to server: " << message << std::endl;
    }

    close(sock);
    std::cout << "Connection closed." << std::endl;
    return 0;
}
