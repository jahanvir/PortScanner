#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool isPortOpen(const std::string& ipAddress, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return false;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    server.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0) {
        close(sock);
        return true;
    }

    close(sock);
    return false;
}

int main() {
    std::string ipAddress;
    std::cout << "Enter the IP address or hostname: ";
    std::cin >> ipAddress;

    std::cout << "Scanning ports for " << ipAddress << "...\n";

    for (int port = 1; port <= 65535; ++port) {
        if (isPortOpen(ipAddress, port)) {
            std::cout << "Port " << port << " is open.\n";
        }
    }

    std::cout << "Port scanning completed.\n";

    return 0;
}
