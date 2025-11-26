#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct command {
    private:
    std::string name;
    std::vector<std::string> args;
    
    public:
    command() : name(""), args({}) {}

    command(std::string commandName) : name(commandName), args({}) {}

    command(const std::string& cmd_name, const std::vector<std::string>& cmd_args)
        : name(cmd_name), args(cmd_args) {}

    const std::string& getName() const {
        return name;
    }

    const std::vector<std::string>& getArgs() const {
        return args;
    }

    void setName(const std::string& cmd_name) {
        name = cmd_name;
    }

    void setArgs(const std::vector<std::string>& cmd_args) {
        args = cmd_args;
    }

    void addArg(const std::string& arg) {
        args.push_back(arg);
    }

    std::string toString() const {
        std::string result = "Command: " + name + "\nArguments:";
        for (const auto& arg : args) {
            result += " " + arg;
        }
        return result;
    }
};

struct helpCommand{
    private:
        // Help text for the help command (*More commands to be added)
        std::string helpText =
        //TODO: NEED LOGIC TO PULL COMMAND LIST FROM COMMANDS.TXT
        "Available Commands:\n"
        "1. help - Display this help message\n"
        "2. adduser - Add a new user\n"
        "3. exit - Exit the shell\n";
        command helpCmd = command("help", {});
        
        
        public:
        // Constructor
        helpCommand() {
            helpCmd.setName("help");
            helpCmd.setArgs({});
        }
        
        void execute() {
            std::cout << helpText << std::endl;
        }
        

};

struct addUserCommand{
    private:
        command userCommand = command("adduser", {});
    
    public:
    // Constructor
    addUserCommand(std::vector<std::string> args) {
        userCommand.setName("adduser");
        userCommand.setArgs(args);
    }

    void execute() {
    // 1. Get the arguments vector
    const auto& args = userCommand.getArgs();
    
    // 2. Check for the correct number of arguments (must be exactly 1: the username)
    if (args.size() != 1) {
        std::cerr << "Error: Incorrect number of arguments. Usage: adduser [username] " << std::endl;
        return;
    }
    const std::string& username = args[0];
    
    std::cout << "Executing adduser command for user: " << username << std::endl;
    
    // --- File Operations ---
    std::string filePath = "C:/Users/spm51/Documents/users.txt";

    // Check if user already exists by reading the file (if it exists)
    {
        std::ifstream usersFileRead(filePath);
        if (usersFileRead.is_open()) {
            std::string line;
            while (std::getline(usersFileRead, line)) {
                std::istringstream iss(line);
                std::string existingUser;
                if (iss >> existingUser) {
                    if (existingUser == username) {
                        std::cerr << "Error: User already exists: " << username << std::endl;
                        return;
                    }
                }
            }
        }
    }

    // Now open for append and add the new user
    std::ofstream usersFile(filePath, std::ios::app);
    if (!usersFile.is_open()) {
        std::cerr << "Error: Unable to open or create users file at: " << filePath << std::endl;
        return;
    }

    // 4. Prompt for and read the password
    std::cout << "Enter user password: ";
    std::string password;
    std::cin >> password;

    // 5. Append username and password (separated by a space, on a new line)
    usersFile << username << " " << password << std::endl;
    
    // 6. Close the file and confirm
    usersFile.close();
    std::cout << "User added successfully: " << username << std::endl; 
}

};