#include <string>
#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include <set>

//  Convert string to 0MQ string and send to socket
static bool s_send (zmq::socket_t & socket, const std::string & string);
//  Receive 0MQ string from socket and convert into string
static std::string s_recv (zmq::socket_t & socket);

int main()
{
    zmq::context_t context(1);
    //  First, connect our subscriber socket
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5561");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //  Second, synchronize with publisher
    zmq::socket_t syncclient (context, ZMQ_REQ);
    syncclient.connect("tcp://localhost:5562");

    //  - send a synchronization request
    s_send (syncclient, "");

    //  - wait for synchronization reply
    s_recv (syncclient);

    //  Third, get our updates and report how many we got
    std::set <std::string> allStudentsSet;
    std::set<unsigned long>::iterator it;
    while (1) {
        zmq::message_t message;
        subscriber.recv(&message);
        std::string student(static_cast<char*>(message.data()), message.size());
        if (student.compare("END") == 0) {
            break;
        }
        allStudentsSet.insert(student);
    }
    for (auto it : allStudentsSet) std::cout << it << std::endl;
    return 0;
}

//  Convert string to 0MQ string and send to socket
static bool s_send (zmq::socket_t & socket, const std::string & string) {
    zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());

    bool rc = socket.send(message);
    return (rc);
}

//  Receive 0MQ string from socket and convert into string
static std::string s_recv (zmq::socket_t & socket) {
    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}
