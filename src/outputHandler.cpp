#include "outputHandler.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sys/socket.h>

namespace bz{ 
    OutputHandler::OutputHandler(){ 
    }
    OutputHandler::OutputHandler(const std::string& filePath){ 
        std::ofstream file(filePath);
        if (!file.is_open()){ 
            throw std::runtime_error("error: can't open file..." + filePath);
        }
        file.close();
    }
    OutputHandler::OutputHandler(const std::string& filePath, int socket){
        if (socket <= 0) {
            throw std::invalid_argument("wrong socket...");
        }
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("error: can't open file..." + filePath);
        }
        file.close(); 
    }
    void OutputHandler::writeToConsole(const std::string& data){ 
        std::cout << data << std::endl;
    }
    void OutputHandler::writeToFile(const std::string& filePath, const std::string& data) {
        std::ofstream file(filePath, std::ios::app); 
        if (!file.is_open()) {
            throw std::runtime_error("error: can't open file..." + filePath);
        }
        file << data << std::endl;
        file.close();
    }
    void OutputHandler::sendToSocket(int socket, const std::string& data) {
        if (socket <= 0) {
            throw std::invalid_argument("wrong socket");
        }

        ssize_t bytesSent = send(socket, data.c_str(), data.size(), 0);
        if (bytesSent == -1) {
            throw std::runtime_error("error: can't send data to socket");
        }
    }
}