#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <zmq.hpp>
//#include "zhelpers.hpp"
#include <bits/stdc++.h>

void readFileInSet(auto& allStudentsSet, std::ifstream& studentFile);

int main(int argc, char* argv[]) 
{
    std::unordered_set <std::string> allStudentsSet;
    if (argc < 3) {
        std::cout << "files not found\n";
        return -1;
    }
    else {
        std::ifstream studentFile1 (argv[2]);
        std::ifstream studentFile2 (argv[3]);
        if (studentFile1.is_open() && studentFile2.is_open()) {
            readFileInSet(allStudentsSet, studentFile1);
            readFileInSet(allStudentsSet, studentFile2);
            
            for(auto i : allStudentsSet) std::cout << i << std::endl;
        }
        else {
            std::cout << "files can't be opened\n";
            return -1;
        }
    }
     
    // initialize the zmq context with a single IO thread
    zmq::context_t context(1);

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5555");

    // prepare some static data for responses
    const std::string data{"World"};

    while (true) 
    {
        zmq::message_t message(allStudentsSet.begin(), allStudentsSet.end());
        // simulate work
        // snprintf((string)message.data(), 1, 
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // send the reply to the client
        publisher.send(message,zmq::send_flags::dontwait); 
    }

    return 0;
}


void readFileInSet(auto& allStudentsSet, std::ifstream& studentFile) {
    std::string valueSet, tmp;
    int keySet;

    while (getline(studentFile, valueSet)) {
        int i = 0;
        while (valueSet[i] != ' ') {
            i++;
        }
        valueSet.erase(0, i+1); 
        allStudentsSet.insert(valueSet);
    }
}
