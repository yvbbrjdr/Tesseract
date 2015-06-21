#define _DEFAULT_MESSAGE_PORT 2333
#define _DEFAULT_SOUND_PORT 2444
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <zmq.h>
#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
    #define sleep(n) Sleep(n)
#endif
#define _PLAYER_MOVE 0
#define _BLOCK_CREATE 1
#define _BLOCK_DESTROY 2
#define _SOUND 3
#define _NEW_USER 4
using namespace std;
