#include "afx.h"
#include "parser.h"
//require libsodium and ØMQ
int main()
{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:2333");

    parser P;
    while (true) {
        zmq::message_t request;
        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received Request" << std::endl;
        //  Send reply back to client
        P.parse(request.data());
        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "RECVD", 5);
        socket.send (reply);
    }
    return 0;
    
}