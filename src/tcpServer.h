#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>

class TCPServer {
public:
    TCPServer(const std::string &address, int port);
    void start();
private:
    std::string address;
    int port;
};

#endif // TCPSERVER_H
