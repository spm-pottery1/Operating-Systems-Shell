#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include "user.c++"

struct login {
    private:
        std::string checkUsername;
        // NOTE: Changed filePath to include a filename for directory separation
        std::string filePath = "C:/Users/spm51/Documents/root/users.txt"; 
        user currentUser = user("root", "root");
        bool loggedIn = false;
    
        public:
        login() {
            checkFirstLogin();
        }

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

        std::string getFilePath() const {
            return filePath;
        }

        void checkFirstLogin() {
            // 1. Get the directory path from the file path
            std::filesystem::path file_path_obj(filePath);
            std::filesystem::path dir_path_obj = file_path_obj.parent_path();

            // 2. Check if the directory exists and create it if it doesn't.
            if (!std::filesystem::exists(dir_path_obj)) {
                try {
                    if (std::filesystem::create_directories(dir_path_obj)) {
                        std::cout << "Created directory: " << dir_path_obj.string() << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error creating directory: " << e.what() << std::endl;
                }
            }
            
            // 3. Check for the file
            std::ifstream userFile(filePath);
            
            if (!userFile.is_open()) {
                // File does not exist, create it and add default root user
                std::ofstream newUserFile(filePath);
                if (newUserFile.is_open()) {
                    newUserFile << "root root" << std::endl;
                    newUserFile.close();
                        std::cout << "Created users file with default root user." << std::endl;
                } else {
                    std::cerr << "Error: Could not create users file." << std::endl;
                }
            } else {
                userFile.close(); // File exists, just close it
            }
        }

        // Method to check if a user exists
        user checkUser(std::string username) const {

            std::ifstream userFile(filePath);
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

            // --- Password Check ---
            std::cout << "Enter password: ";
            std::cin >> inputPassword;
            std::cout << "DEBUG: Input password is [" << inputPassword << "]" << std::endl;
            std::cout << "DEBUG: Stored password is [" << currentUser.getPassword() << "]" << std::endl;

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