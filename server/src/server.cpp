#include "server.h"

#include "user.h"

#include <iostream>

namespace server {

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::error_code;
using namespace websocketpp::frame;

Server::Server() {
    SetLogging(&std::cerr);

    server_.init_asio();
            
    server_.set_open_handler(bind(&Server::OpenHandler, this, _1));
    server_.set_close_handler(bind(&Server::CloseHandler, this, _1));
    server_.set_message_handler(bind(&Server::MessageHandler, this, _1, _2));
}

// setting logging
void Server::SetLogging(std::ostream* log) {
    // logging everything but debug/development information
    server_.set_access_channels(websocketpp::log::alevel::all);
    server_.clear_access_channels(websocketpp::log::alevel::debug_handshake |
                                  websocketpp::log::alevel::debug_close |
                                  websocketpp::log::alevel::devel);
    server_.set_error_channels(websocketpp::log::elevel::all);
    server_.clear_error_channels(websocketpp::log::elevel::devel);

    server_.get_alog().set_ostream(log);
    server_.get_elog().set_ostream(log);
}

void Server::OpenHandler(connection_hdl hdl) {
    user_list_.AddUser(std::move(hdl));
}

void Server::CloseHandler(connection_hdl hdl) {
    user_list_.RemoveUser(std::move(hdl));
}

void Server::MessageHandler(
        connection_hdl hdl, Server::ServerEndpoint::message_ptr msg) {
    static const std::string cmd_indicator = "/";
    static const size_t cmd_indicator_size = cmd_indicator.size();
    static const std::string username_cmd = "username";
    static const std::string tell_cmd = "tell";
    static const std::string userlist_cmd = "userlist";

    // this lambda returns a lexeme began with the position _idx as new string
    // also it moves the index to the begin of next lexeme
    // if _idx points to ' ' returns "" and move index to begin of next lexeme
    auto next_lexeme_lambda = [](size_t& idx, const std::string& str) {
        std::string res;

        if (idx < 0)
            idx = 0;

        while (true) {
            if (idx >= str.size())
                break;

            if (str[idx] == ' ') {
                while (true) {
                    if (idx == (int)str.size())
                        break;
                    if (str[idx] != ' ')
                        break;
                    idx++;
                }
                break;
            }

            res.push_back(str[idx]);
            idx++;
        }

        return res;
    };


    // parsing message
    if (msg->get_opcode() == opcode::text && user_list_.IsUserExist(hdl)) {
        shared_ptr<const User> user = user_list_.GetUser(hdl);
        std::string msg_str = msg->get_payload();

        size_t idx = 0;

        if (msg_str.substr(idx, cmd_indicator_size) == cmd_indicator) {
            idx += cmd_indicator_size;

            std::string cmd = next_lexeme_lambda(idx, msg_str);

            if (cmd == username_cmd) {
                std::string new_username = next_lexeme_lambda(idx, msg_str);
                ChangeUsername(user, new_username);
            } else if (cmd == tell_cmd) {
                std::string receiver_username =
                        next_lexeme_lambda(idx, msg_str);
                SendPrivateMessage(user,
                                   receiver_username,
                                   msg_str.substr(idx, std::string::npos));
            } else if (cmd == userlist_cmd) {
                SendUserlist(user);
            } else {
                UnknownCommandHandler(user);
            }
        } else {
            SendGlobalMessage(user, msg_str);
        }
    }
}

// server loop
void Server::Run(uint16_t port) {
    server_.listen(port);
    server_.start_accept();
    server_.run();
}

void Server::SendMessage(
        shared_ptr<const User> receiver, const std::string& msg) {
    server_.send(receiver->GetConnection(), msg, opcode::text);
}

void Server::SendPrivateMessage(shared_ptr<const User> sender,
                                const std::string& receiver_username,
                                const std::string& msg) {
    if (user_list_.IsUserExist(receiver_username)) {
        static const std::string private_msg_prefix = "P ";

        std::string msg_res =
                private_msg_prefix + sender->GetUsername() + ": " + msg;
        shared_ptr<const User> receiver =
                user_list_.GetUser(receiver_username);

        SendMessage(receiver, msg_res);
    } else {
        static const std::string unknown_user_msg =
                "User with such username doesn't exist or disconnected.";

        SendMessage(sender, unknown_user_msg);
    }
}

// SendGlobalMessage and BroadcastMessage divided for cases
// when the server wants to send a message to all users without exlusions

void Server::SendGlobalMessage(
        shared_ptr<const User> sender, const std::string& msg) {
    static const std::string global_msg_prefix = "G ";

    std::string res_msg =
            global_msg_prefix + sender->GetUsername() + ": " + msg;
    BroadcastMessage(sender, res_msg);
}

// exclusion = nullptr to send a message to all  users
void Server::BroadcastMessage(
            shared_ptr<const User> exclusion, const std::string& msg) {
    for (const auto& user_ptr : user_list_.GetUserSet())
        if(exclusion.get() != user_ptr.get())
            SendMessage(user_ptr, msg);
}

// form and send full list of usernames
void Server::SendUserlist(shared_ptr<const User> receiver) {
    std::string msg = "User List:";
    for (const auto& user_ptr : user_list_.GetUserSet()) {
        msg += ("\n" + user_ptr->GetUsername());
        if(receiver.get() == user_ptr.get())
            msg += " [You]";
    }

    SendMessage(receiver, msg);
}

// username is unique
void Server::ChangeUsername(
            shared_ptr<const User> user, const std::string& username) {
    static const std::string success_msg_prefix =
            "Your username successfuly changed to ";
    static const std::string failed_msg =
            "Username changing failed. Probably user with such username"
            " already exist.";
    static const std::string invalid_msg =
            "Invalid username. Usernames can only contain letters and numbers.";

    if (!User::IsUsernameValid(username)) {
        SendMessage(user, invalid_msg);
        return ;
    }

    std::string old_username = user->GetUsername();
    if (user_list_.SetUsername(user, username)) {
        std::string success_msg = success_msg_prefix + username + ".";
        SendMessage(user, success_msg);

        std::string user_changed_name_msg =
                old_username + " changed username to " + username + ".";
        BroadcastMessage(user, user_changed_name_msg);
    } else {
        SendMessage(user, failed_msg);
    }
}

void Server::UnknownCommandHandler(shared_ptr<const User> user) {
    static const std::string unknown_cmd_msg = "Unknown command.";

    SendMessage(std::move(user), unknown_cmd_msg);
}

}  // namespace server
