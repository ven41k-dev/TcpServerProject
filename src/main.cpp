#include "tcpServer.h"  // Додаємо заголовок для класу TCPServer

int main() {
    // Створюємо сервер на IP 127.0.0.1 і порт 5000
    TCPServer server("127.0.0.1", 5000);

    // Запускаємо сервер
    server.start();

    return 0;
}
