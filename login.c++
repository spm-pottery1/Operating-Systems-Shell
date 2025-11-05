#include <fstream>
#include <iostream>
#include <string>
#include "user.c++"

struct login {
    private:
        std::string checkUsername;
        user currentUser = user("root", "root");
        bool loggedIn = false;
    public:
        login() {}

        void displayUserInfo() const {
            if (loggedIn == true) {
                std::cout << currentUser.toString() << std::endl;
            } else {
                std::cout << "No user is currently logged in." << std::endl;
            }
        }

        void setLoggedIn(bool status) {
            loggedIn = status;
        }

        bool isLoggedIn() const {
            return loggedIn;
        }

        // Method to check if a user exists
user checkUser(std::string username) const {

    std::ifstream userFile("C:/Users/spm51/Documents/users.txt");
    if(!userFile.is_open()) {
        std::cerr << "No open file in login::checkUser" << std::endl;
        return user("", ""); // Return empty user on file open failure
    }

    std::string userNameFromFile;
    std::string passwordFromFile;

    while(userFile >> userNameFromFile >> passwordFromFile) {
        if(userNameFromFile == username) {
            user foundUser(userNameFromFile, passwordFromFile);
            return foundUser;
        }
    }
    std::cout << "User not found in login::checkUser" << std::endl;
    return user("", ""); // Return empty user if not found
}

        // Authentication method for login
bool authenticate() {
    std::string inputUsername;
    std::string inputPassword;
    
    // --- Loop for Username Validation ---
    do {
        std::cout << "Enter username: ";
        std::cin >> inputUsername;

        // Try to find the user in the file
        currentUser = checkUser(inputUsername); 

        // If user not found (or file open failed and checkUser returned empty)
        if (currentUser.getUsername() == "") {
            std::cout << "User not found or file error. Please try again." << std::endl;
        }

    // Keep looping while the username is empty/not found
    } while (currentUser.getUsername() == ""); 

    // Username accepted
    std::cout << "Username accepted: " << currentUser.getUsername() << std::endl; 

    //std::cout << "DEBUG: Retrieved password is [" << currentUser.getPassword() << "]" << std::endl;
    //std::cout << "DEBUG: Input PWD length: " << currentUser.getPassword().length() << std::endl;
    
    // --- Password Check ---
    std::cout << "Enter password: ";
    std::cin >> inputPassword;

    // Check if the retrieved user's password matches the input
    setLoggedIn(currentUser.getPassword() == inputPassword);
    return isLoggedIn();

    }

        // Password authentication method
    bool passAuthenticate() {
            
        std::string inputPassword;
        std::cout << "Enter password: ";
        std::cin >> inputPassword;

        return (currentUser.getPassword() == inputPassword);
    }

};
