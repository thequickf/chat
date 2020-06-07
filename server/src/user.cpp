#include "user.h"

namespace server {

int User::next_user_id_ = 0;

User::User(connection_hdl connection) : connection_(std::move(connection)) {
    // the username has to be unique 
    username_ = std::to_string(next_user_id_++);
}

User::User(connection_hdl connection, std::string username) :
        connection_(std::move(connection)),
        username_(std::move(username)) {}

std::string User::GetUsername() const {
    return username_;
}

connection_hdl User::GetConnection() const {
    return connection_;
}

// username have length limit and can contain only latin letters and numbers
bool User::IsUsernameValid(const std::string& username) {
    static const int lower_limit = 1;
    static const int upper_limit = 20;

    int length = username.size();
    if (length < lower_limit || length > upper_limit)
        return false;

    for (const char c : username) {
        bool ok = false;
        if (c >= 'a' && c <= 'z')
            ok = true;
        if (c >= 'A' && c <= 'Z')
            ok = true;
        if (c >= '0' && c <= '9')
            ok = true;

        if (!ok)
            return false;
    }

    return true;
}

void User::SetUsername(const std::string& username) {
    username_ = username;
}

}
