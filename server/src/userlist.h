#ifndef USERLIST_H
#define USERLIST_H

#include <map>
#include <set>
#include <string>

#include <websocketpp/common/connection_hdl.hpp>

namespace server {

using websocketpp::connection_hdl;
using websocketpp::lib::shared_ptr;

class User;

// container for User with fast access to elements by username or connection_hdl
// access: O(logN)
// insert: O(logN)
// remove: O(logN)
class UserList {
    typedef std::map<connection_hdl,
                     shared_ptr<User>,
                     std::owner_less<connection_hdl>> ConnectionToUserMap;
    typedef std::map<std::string, shared_ptr<User>> UsernameToUserMap;
    typedef std::set<
        std::shared_ptr<User>, std::owner_less<shared_ptr<User>>> UserSet;

public:
    UserList();

    // connection_hdl is a weak pointer so it's ok to copy it
    bool AddUser(connection_hdl connection);
    bool RemoveUser(connection_hdl connection);
    
    std::string GetUsername(connection_hdl connection) const;
    bool SetUsername(connection_hdl connection, const std::string& username);
    bool SetUsername(shared_ptr<const User> user, const std::string& username);

    connection_hdl GetConnection(const std::string& username) const;
    shared_ptr<const User> GetUser(connection_hdl connection) const;
    shared_ptr<const User> GetUser(const std::string& username) const;
    bool IsUserExist(connection_hdl connection) const;
    bool IsUserExist(const std::string& username) const;
    const UserSet& GetUserSet() const;

protected:
    std::string GetUniqueUsername() const;

private:
    // this containers can be changed only with: AddUser, RemoveUser, SetUsername
    ConnectionToUserMap connection_to_user_map; // connection_hdl to User
    UsernameToUserMap username_to_user_map; // username to User
    UserSet user_set; // container of all User's
};

}  // namespace server

#endif // USERLIST_H
