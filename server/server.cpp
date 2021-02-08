#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <zmq.hpp>
#include <bits/stdc++.h>

void readFileInSet(auto& allStudentsSet, std::ifstream& studentFile);

int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        std::cout << "files not found\n";
        return -1;
    }
    else {
        std::ifstream studentFile1 (argv[2]);
        std::ifstream studentFile2 (argv[3]);
        if (studentFile1.is_open() && studentFile2.is_open()) {
            std::unordered_set <std::string> allStudentsSet;

            readFileInSet(allStudentsSet, studentFile1);
            readFileInSet(allStudentsSet, studentFile2);
            
            for(auto i : allStudentsSet) std::cout << i << std::endl;
        }
        else {
            std::cout << "files can't be opened\n";
            return -1;
        }
    } 
    using namespace std::chrono_literals;

    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    // prepare some static data for responses
    const std::string data{"World"};

    for (;;) 
    {
        zmq::message_t request;
        // receive a request from client
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " << request.to_string() << std::endl;

        // simulate work
        std::this_thread::sleep_for(3s);

        // send the reply to the client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
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
