#ifndef SERVER_H
#define SERVER_H

#include "userlist.h"

#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

namespace server {

class User;

using websocketpp::connection_hdl;
using websocketpp::lib::shared_ptr;

// main class for this application
// handles connections and messages
class Server {
    typedef websocketpp::server<websocketpp::config::asio> ServerEndpoint;

public:
    Server();

    void SetLogging(std::ostream* log);
    
    void OpenHandler(connection_hdl hdl);
    void CloseHandler(connection_hdl hdl);
    void MessageHandler(connection_hdl idx, ServerEndpoint::message_ptr str);
    
    void Run(uint16_t port);

protected:
    void SendMessage(
            shared_ptr<const User> receiver, const std::string& msg);
    void SendPrivateMessage(shared_ptr<const User> sender,
                            const std::string& receiver_username,
                            const std::string& msg);
    void SendGlobalMessage(
            shared_ptr<const User> sender, const std::string& msg);
    void BroadcastMessage(
            shared_ptr<const User> exclusion, const std::string& msg);
    void SendUserlist(shared_ptr<const User> receiver);
    void ChangeUsername(
            shared_ptr<const User> user, const std::string& username);
    void UnknownCommandHandler(shared_ptr<const User> user);

    ServerEndpoint server_; // websocketpp server endpoint
    UserList user_list_; // User container
};

}  // namespace server

#endif // SERVER_H
