#include "afx.h"
#include "playerlist.h"
void broadcastfrom(string un, string strmsg)
{
    string msg=un+"@"+strmsg;
    void* bcContext = zmq_ctx_new();
    void* publisher = zmq_socket(bcContext, ZMQ_PUB);
    assert(zmq_bind(publisher, "tcp://*:1998") ==0);
    char* cSend = msg.data();
    zmq_msg_t msg;
    zmq_msg_init_size(&msg,strlen(cSend)+1);
    memcpy(zmq_msg_data(&msg), cSend, strlen(cSend)+1);
    zmq_msg_send(&msg, publisher, 0);
    zmq_msg_close(&msg);
    zmq_msg_close(publisher);
    zmq_ctx_destroy(context);
    return;
}