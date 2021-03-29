#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <zmq.hpp>
#include <unistd.h>
#include <bits/stdc++.h> //for unordered_set

#define SIZE_OF_MESSAGE 12
#define SUBSCRIBERS_EXPECTED 1

typedef std::unordered_set <std::string> SetOfStrings;

void readFileInSet(SetOfStrings& allStudentsSet, std::ifstream& studentFile);
static bool s_send (zmq::socket_t & socket, const std::string & string);

int main(int argc, char* argv[]) 
{
    SetOfStrings allStudentsSet;
    std::set<unsigned long>::iterator it;

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
        }
        else {
            std::cout << "files can't be opened\n";
            return -1;
        }
    }
    zmq::context_t context(1);
    zmq::socket_t publisher (context, ZMQ_PUB);

    int sndhwm = 0;
    publisher.setsockopt (ZMQ_SNDHWM, &sndhwm, sizeof (sndhwm));

    publisher.bind("tcp://*:5561");

    //  Socket to receive signals
    zmq::socket_t syncservice (context, ZMQ_REP);
    syncservice.bind("tcp://*:5562");

    //  Get synchronization from subscribers
    int subscribers = 0;
    while (subscribers < SUBSCRIBERS_EXPECTED) {
        
        //  - wait for synchronization request
        zmq::message_t request;
        syncservice.recv(&request); 
       
        //  - send synchronization reply
        s_send (syncservice, "");
    }
    
    for(auto it : allStudentsSet) {  
        s_send (publisher, it);
    }
    
    s_send (publisher, "END");
    sleep (1);              //  Give 0MQ time to flush output
    return 0;
} 

void readFileInSet(SetOfStrings& allStudentsSet, std::ifstream& studentFile) {
    std::string valueSet;

    while (getline(studentFile, valueSet)) {
        int i = 0;
        while (valueSet[i] != ' ') {
            i++;
        }
        valueSet.erase(0, i+1); 
        allStudentsSet.insert(valueSet);
    }
}

//  Convert string to 0MQ string and send to socket
static bool s_send (zmq::socket_t & socket, const std::string & string) {
    zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());

    bool rc = socket.send(message);
    return (rc);
}
