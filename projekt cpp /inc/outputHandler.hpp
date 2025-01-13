#pragma once 

#include <string> 

namespace bz{

class OutputHandler { 
    public: 
        OutputHandler(); 
        OutputHandler(const std::string& filePath);
        OutputHandler(const std::string& filePath, int socket);

        void writeToConsole(const std::string& data);
        void writeToFile(const std::string& filePath, const std::string& data); 
        void sendToSocket(int socket, const std::string& data); 
};
}

