#include <iostream>
#include <string>
#include "directory.c++"
#include <fstream>
#include <sstream>
#include <vector>

struct user {
    private:
        std::string username;
        std::string password;
        std::vector<Directory> directories;
        std::vector<File> files;
        
        int userId;
        int dirIdCounter = 0;
        int fileIdCounter = 0;
        int permissions = 0; // Placeholder for future permission management

        


    public:

    // Constructor
    user(const std::string& u, const std::string& p)
        : username(u), password(p) {}

    // Getters
    const std::string& getUsername() const { 
        return username; 
    }
    const std::string& getPassword() const { 
        return password; 
    }
    const std::vector<Directory>& getDirectories() const { 
        return directories; 
    }
    const std::vector<File>& getFiles() const { 
        return files; 
    }

    int getUserId() const { 
        return userId; 
    }

    int getPermissions() const { 
        return permissions; 
    }

    // Setters
    void setUsername(const std::string& u) { 
        username = u; 
    }

    void setPassword(const std::string& p) { 
        password = p; 
    }

    void addDirectory(const Directory& dir) { 
        directories.push_back(dir); 
    }

    void addFile(const File& file) { 
        files.push_back(file); 
    }

    int NextDirId() { 
        return ++dirIdCounter; 
    }

    int NextFileId() { 
        return ++fileIdCounter; 
    }

    void setUserId(int id) { 
        userId = id; 
    }

    void setPermissions(int perms) { 
        permissions = perms; 
    }

    // toString method
    std::string toString() const {
        return "Username: " + username + "\n" +
               "Password: " + password + "\n" +
               "Directories: " + std::to_string(directories.size()) + "\n" +
               "Files: " + std::to_string(files.size());
    }

    void buildUser() {
    // Note: The file stream object should be userFile, not users.txt, 
    // but assuming this is the definition within user.c++:
    std::ifstream userFile("users.txt"); 
    if (!userFile.is_open()) {
        // Log an error or handle the failure gracefully
        std::cerr << "Warning: Could not open users.txt in buildUser for auxiliary data." << std::endl;
        return; 
    }
    std::string line;
    while (std::getline(userFile, line)) {
        std::istringstream iss(line);
        std::string u, p; 
        // Temporarily read username and password to find the correct line
        if (iss >> u >> p) {
            // Found the line for the current user
            if (u == username) {
                // Read additional data as needed
                password = p;
                return; 
            }
        }
    // File automatically closes when userFile goes out of scope (RAII)
    }
}
};