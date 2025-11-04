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

int main() {    
    
    
    
    
    
    return 0;
}