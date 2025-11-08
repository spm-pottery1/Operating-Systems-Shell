#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include "comand.c++"

struct colonel {
    private:
    int command_id_counter = 0;
    std::unordered_map<std::string, int> command_list;
    std::vector<std::string> parsed_command;
    std::vector<command> command_objects;
    std::vector<std::string> command_args;
    
    command buildCommand(const std::string& cmd_name, const std::vector<std::string>& cmd_args) {
        command_id_counter++;
        command newCommand(cmd_name, cmd_args);
        command_objects.push_back(newCommand);
        command_list[cmd_name] = command_id_counter;
        return newCommand;
    }

    void initColonel() {
        // Initialize kernel components here
        /*
            Something like:
            for(command in commands.txt) {
                command_list[command] = command_id++;
            }
            command_id_counter = command_id;  
        */
        buildCommand("help", {});
        buildCommand("exit", {});
        std::cout << "DEBUG(COLONEL.C++, initColonel()): Colonel initialized with " 
                  << command_list.size() << " commands." << std::endl;
    }

    const std::vector<std::string>& getParsedCommand(const std::string& user_command) {
        parsed_command.clear();
        std::stringstream ss(user_command);
        std::string command;
        while (ss >> command) {
            parsed_command.push_back(command);

        }
        return parsed_command;
    }

    int commandExists(const std::string& command_name) {
        auto it = command_list.find(command_name);
        if (it != command_list.end()) {
            return it->second; // Return command ID
        }
        return -1; // Command not found
    }


    public:
    // Constructor
    colonel() {
        initColonel();
    }

    // Method to parse and execute a command
    const std::string parseCommand(const std::string& user_command) {
    std::vector<std::string> tokens = getParsedCommand(user_command);
    
    // 1. Check for empty command
    if (tokens.empty()) {
        return ""; // Nothing to do
    }

    // 2. Only check the FIRST token for the command name
    const std::string& command_name = tokens[0];
    int cmd_id = commandExists(command_name); 

    if (cmd_id != -1) {
        std::cout << "DEBUG(COLONEL.C++, parseCommand()): Executing command ID: " << cmd_id << std::endl;
        switch(cmd_id) {
            case 1: // help command
                {
                    helpCommand helpCmd;
                    helpCmd.execute();
                    return "Help command executed.";
                }
            case 2: //adduser command
                {
                    // Placeholder for adduser command logic
                    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
                    addUserCommand addUserCmd(args);
                    return "AddUser command executed.";
                }
            default:
                return "Command execution logic not implemented yet.";
        }
    }
    else {
        std::cout << "Command not found: " << command_name << std::endl;
        return "";
    }
    }



};