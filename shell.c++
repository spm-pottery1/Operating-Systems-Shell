#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ctime> 
#include "login.c++"

// Reads credentials from the `login` file in the repository root.
// File format: one credential per line: "username password"
// Returns a map of username -> password.
static void login_user(login &handler) {
    bool login = handler.authenticate();
    if (login) {
        std::cout << "Login successful!" << std::endl;
        handler.displayUserInfo();
    } else {
        std::cout << "Login failed." << std::endl;
    }
}

int main() {    

    login loginHandler;
    login_user(loginHandler);
    while(loginHandler.isLoggedIn() == true) {
        std::cout << "Shell>> ";
        std::string command;
        std::cin >> command;
        if (command == "exit") {
            loginHandler.setLoggedIn(false);
            std::cout << "Logged out successfully." << std::endl;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
    }


    return 0;
}
};