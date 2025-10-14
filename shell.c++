#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ctime> 

// Reads credentials from the `login` file in the repository root.
// File format: one credential per line: "username password"
// Returns a map of username -> password.
static std::unordered_map<std::string, std::string> read_login_file(const std::string &path) {
    std::unordered_map<std::string, std::string> creds;
    std::ifstream in(path);
    if (!in) return creds; // empty map if file can't be opened

    std::string user, pass;
    while (in >> user >> pass) {
        creds[user] = pass;
    }
    return creds;
}

void log_message(const std::string& message) {
    // Open log file in append mode (std::ios::app)
    // The log file path is hardcoded here ("log")
    std::ofstream logFile("log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "CRITICAL LOGGING ERROR: Cannot open 'log' file.\n";
        return;
    }

    // Get current time and format it
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    
    // Declare buffer for formatted timestamp
    char buffer[32]; 
    
    // Write timestamp and message
    std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", &tm);
    
    // The time is now formatted in 'buffer' and is written to the file
    logFile << buffer << " " << message << "\n";
}

// LOGICAL CHANGE: Removed the unused 'logPath' parameter from the login function signature.
int login(std::string loginPath) {
    auto creds = read_login_file(loginPath);
    if (creds.empty()) {
        std::cerr << "Warning: no credentials found in '" << loginPath << "'.\n";
        std::cerr << "Falling back to default account: admin/password\n";
        creds["admin"] = "password";
    }

    bool loggedIn = false;
    while (!loggedIn) {
        std::string username, password;
        std::cout << "Enter username: ";
        if (!(std::cin >> username)) break;
        std::cout << "Enter password: ";
        if (!(std::cin >> password)) break;

        auto it = creds.find(username);

        
        if (it != creds.end() && it->second == password) {
            loggedIn = true;
            std::cout << "Login successful!" << std::endl;
            log_message("User '" + username + "' logged in successfully.");
            
        } else {
            std::cout << "Invalid credentials. Please try again." << std::endl;
            log_message("Failed login attempt for username: " + username);
        }
    }

    return loggedIn ? 0 : 1;
}

int addUser(std::string loginPath) {
    std::ofstream out(loginPath, std::ios::app);
    if (!out) {
        std::cerr << "Error: could not open '" << loginPath << "' for appending.\n";
        return 1;
    }

    std::string newUser, newPass;
    std::cout << "Enter new username: ";
    if (!(std::cin >> newUser)) return 1;
    std::cout << "Enter new password: ";
    if (!(std::cin >> newPass)) return 1;

    out << newUser << " " << newPass << "\n";
    std::cout << "User '" << newUser << "' added successfully.\n";
    log_message("Added new user: " + newUser);
    return 0;
}

int main() {

    int exitCode = 0;
    const std::string loginPath = "login"; 
    log_message("--Start Session--");
    // Removed unused logPath variable, as it's hardcoded in log_message

    // LOGICAL CHANGE: Updated the function call to match the new signature
    int rc = login(loginPath); 


    if (rc == 0){
        std::cout << "\n--- Application Shell Running ---\n";
        std::cout << "Available Commands: 'adduser', 'exit'\n";
        
        while(exitCode == 0) { 
            std::string command;
            std::cout << "shell>> ";
            
            if(std::cin >> command) {
                
                if(command == "exit") {
                    log_message("Shell exited by user command."); // Added log for exit
                    exitCode = 1;
                } else if(command == "adduser") {
                    addUser(loginPath);
                } else {
                    std::cout << "Unknown command: " << command << ". Try 'adduser' or 'exit'." << std::endl;
                    log_message("Unknown command attempted: " + command);
                }
                
            } else {
                exitCode = 1;
            }

        }
        std::cout << "Exiting shell...\n";
        log_message("--Logout/EOF--"); // Changed log message slightly
    } else {
        std::cerr << "Login failed. Exiting program.\n";
        exitCode = rc; 
    }
    
    return exitCode;
}