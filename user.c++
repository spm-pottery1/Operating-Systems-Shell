#include <iostream>
#include <string>
#include "directory.c++"
#include "file.c++"



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
};