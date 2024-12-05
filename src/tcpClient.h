#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>

class TcpClient {
public:
    TcpClient(const std::string &serverAddress, int port);
    void connectToServer();
    void sendMessage(const std::string &message);
    void closeConnection();

private:
    int clientSocket;
    std::string serverAddress;
    int port;
};

#endif // TCPCLIENT_H
