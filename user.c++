#include <iostream>
#include <string>
#include "directory.c++"



struct user {
    private:
        std::string username;
        std::string password;
        std::vector<Directory> directories;
        std::vector<File> files;
        
        int userId;
        int dirIdCounter = 0;
        int fileIdCounter = 0;

        


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
};