#ifndef USER_H
#define USER_H

#include <string>

#include <websocketpp/common/connection_hdl.hpp>

using websocketpp::connection_hdl;

namespace server {

class UserList;

// simple class describing user
// basically it's an open connection with username associated to it
class User {

public:
    explicit User(connection_hdl connection);
    User(connection_hdl connection, std::string username);

    std::string GetUsername() const;
    connection_hdl GetConnection() const;

    static bool IsUsernameValid(const std::string& username);

protected:
    friend class UserList;
    void SetUsername(const std::string& username);

    connection_hdl connection_;
    std::string username_;

    // utility static member for username initialization
    static int next_user_id_;
};

}  // namespace server

#endif // USER_H
