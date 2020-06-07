#include "server.h"

int main() {
    uint16_t port = 9002;
    server::Server server;
    server.Run(port);
    return 0;
}
