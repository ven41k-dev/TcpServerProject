#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[1024] = {0};
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Помилка створення сокета\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Неправильна IP-адреса\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Помилка підключення\n";
        return -1;
    }

    while (true) {
        std::cout << "Введіть повідомлення (або 'exit' для виходу): ";
        std::cin.getline(message, sizeof(message));

        if (strcmp(message, "exit") == 0) break;

        send(sock, message, strlen(message), 0);

        int valread = read(sock, buffer, 1024);
        std::cout << "Відповідь від сервера: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
