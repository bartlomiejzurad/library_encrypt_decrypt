#include "inputHandler.hpp"
#include <fstream>
#include <stdexcept> 
#include <sys/socket.h>

namespace bz { 
    InputHandler::InputHandler() 
        : inData(" ") {} 
    InputHandler::InputHandler(const std::string& inData)
        : inData(inData) {} 
    InputHandler::InputHandler(const std::string& inData, int bufferSize)
        : inData(inData) { 
            if (bufferSize != BUFFER_SIZE){ 
                throw std::invalid_argument("buffer size is not equal 1500...");
            }
        }
    void InputHandler::readFromConsole(){ 
        std::cout << "enter your data:  "; 
        std::getline(std::cin, inData);
    }
    void InputHandler::loadFromFile(const std::string& filePath){ 
        std::ifstream file(filePath);
        if (!file.is_open()){ 
            throw std::runtime_error("unable to open your file: " + filePath);
        }
        inData.assign((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
            file.close();
    }
    void InputHandler::receiveFromSocket(int socket){ 
        char buffer[BUFFER_SIZE];
        inData.clear();

        int bytesRead; 
        while ((bytesRead = recv(socket, buffer, BUFFER_SIZE, 0)) > 0){ 
            inData.append(buffer, bytesRead);
        }
        if(bytesRead < 0){ 
            throw std::runtime_error("error receiving your data from socket" + socket);
        }   
    }
    bool InputHandler::validateData(const std::string& data) const {
        return !data.empty();
}
    std::string InputHandler::getData() const{ 
        return inData; 
    }
    bool InputHandler::operator==(const InputHandler& other) const {
        return inData == other.inData;
    }
    bool InputHandler::operator!=(const InputHandler& other) const {
        return !(*this == other);
    }
    InputHandler& InputHandler::operator=(const InputHandler& other) {
        if (this != &other) { 
            inData = other.inData;
        }
        return *this;
    } 
}
