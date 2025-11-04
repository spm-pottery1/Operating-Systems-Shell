#include <iostream>
#include <string>
#include "user.c++"

struct login {
    private:
        user currentUser;
    public:
        login(const user& user) : currentUser(user) {}

        void displayUserInfo() const {
            std::cout << currentUser.toString() << std::endl;
        }

        // Authentication method for login
        bool authenticate() const {
            
            std::string inputUsername;
            std::string inputPassword;

            std::cout << "Enter username: ";
            std::cin >> inputUsername;
            std::cout << "Enter password: ";
            std::cin >> inputPassword;

            return (currentUser.getUsername() == inputUsername && currentUser.getPassword() == inputPassword);
        }

        // Password authentication method
        bool passAuthenticate() const {
            
            std::string inputPassword;
            std::cout << "Enter password: ";
            std::cin >> inputPassword;

            return (currentUser.getPassword() == inputPassword);
        }
};
