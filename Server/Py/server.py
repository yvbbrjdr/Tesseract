#this server will need ZeroMQ and libsodium
import zmq
import sys
import time
import thread

bmsg=''

def REPLY():
    cli = zmq.Context()
    s = cli.socket(zmq.REP)
    s.bind('ipc:///tmp/zmq')
    #or s.bind('tcp://127.0.0.1:1998') is also ok
    while True:
        msg = s.recv_pyobj()
        if msg == 'Hi Server':
            s.send_pyobj(msg)
        else:
            bmsg = msg
            thread.start_new_thread(DELIVER,())
    s.close()
    thread.exit_thread()

def DELIVER():
    bind_to = "tcp://*:2400"
    ctx = zmq.Context()
    s = ctx.socket(zmq.PUB)
    s.bind(bind_to)

    print "Starting broadcast"
    print "Waiting so subscriber sockets can connect..."

    time.sleep(0.5)
    
    try:
        s.send_pyobj(bmsg);
    except KeyboardInterrupt:
        pass

    print "Waiting for message queues to flush..."
    time.sleep(0.5)
    s.close()
    print "Finished successfully."
    
def main():
    REPLY()

if __name__ == "__main__":
    main()
