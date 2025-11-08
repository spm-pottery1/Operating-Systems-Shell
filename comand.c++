#include <iostream>
#include <string>
#include <vector>

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
        "2. exit - Exit the shell\n";
        command helpCmd = command("help", {});
        
        
        public:
        // Constructor
        helpCommand() {
            helpCmd.setName("help");
            helpCmd.setArgs({});
        }
        
        void displayHelp() {
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
};

