#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <zmq.hpp>
#include <bits/stdc++.h>

void readFileInSet(auto& readFileInSet, std::ifstream& studentFile);

int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        std::cout << "File not found\n"; 
    }
    else {
        std::ifstream file1 ("student_file_1.txt");
        if (!file1.is_open()) {
            cout << "File can't open\n";
            return 1;
        }
        else
        {
             
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
