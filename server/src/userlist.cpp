#include "userlist.h"

#include "user.h"

namespace server {

using websocketpp::lib::make_shared;

UserList::UserList() = default;

bool UserList::AddUser(connection_hdl connection) {
    if (!IsUserExist(connection)) {
        // all containers must contain a pointer to the object
        shared_ptr<User> user_ptr =
                make_shared<User>(connection, GetUniqueUsername());
        user_set.insert(user_ptr);
        connection_to_user_map[connection] = user_ptr;
        username_to_user_map[user_ptr->GetUsername()] = user_ptr;

        return true;
    }
    else
        return false;
}

bool UserList::RemoveUser(connection_hdl connection) {
    if (IsUserExist(connection)) {
        // User object deletes automatically
        shared_ptr<User> user_ptr = connection_to_user_map[connection];
        user_set.erase(user_ptr);
        connection_to_user_map.erase(connection);
        username_to_user_map.erase(GetUsername(connection));
        
        return true;
    }
    else
        return false;
}

std::string UserList::GetUsername(connection_hdl connection) const {
    if (IsUserExist(connection))
        return connection_to_user_map.at(connection)->GetUsername();
    else
        return std::string();
}

bool UserList::SetUsername(connection_hdl connection, const std::string& username) {
    if (connection_to_user_map.count(connection) &&
        !username_to_user_map.count(username)) {
        // carefully changing connection_to_user_map
        shared_ptr<User> user_ptr = connection_to_user_map[connection];
        std::string prev_username = GetUsername(connection);
        user_ptr->SetUsername(username);
        username_to_user_map.erase(prev_username);
        username_to_user_map[username] = user_ptr;

        return true;
    }
    else
        return false;
}

bool UserList::SetUsername(
        shared_ptr<const User> user, const std::string& username) {
    return SetUsername(user->GetConnection(), username);
}

connection_hdl UserList::GetConnection(const std::string& username) const {
    if (IsUserExist(username))
        return username_to_user_map.at(username)->GetConnection();
    else
        return connection_hdl();
}

shared_ptr<const User> UserList::GetUser(connection_hdl connection) const {
    if (IsUserExist(connection))
        return connection_to_user_map.at(connection);
    else
        return shared_ptr<const User>(nullptr);
}

shared_ptr<const User> UserList::GetUser(const std::string& username) const {
    if (IsUserExist(username))
        return username_to_user_map.at(username);
    else
        return shared_ptr<const User>(nullptr);
}

bool UserList::IsUserExist(connection_hdl connection) const {
    return connection_to_user_map.count(connection);
}

bool UserList::IsUserExist(const std::string& username) const {
    return username_to_user_map.count(username);
}

const UserList::UserSet& UserList::GetUserSet() const {
    return user_set;
}

// we have to make sure that username is unique
std::string UserList::GetUniqueUsername() const {
    static const int mod = 1e6;

    while (true) {
        std::string username = std::to_string(rand()%mod);
        if(!IsUserExist(username))
            return username;
    }
}

}  // namespace server
