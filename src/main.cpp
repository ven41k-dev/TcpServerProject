#include "tcpServer.h"

int main() {
    TCPServer server("127.0.0.1", 5000);
    server.start();
    return 0;
}
