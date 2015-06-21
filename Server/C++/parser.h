#include "afx.h"
#include "deliver.h"

class parser
{
private:
    string strRecv;
    int dMsgtype;
    string un;
    string strText;
public:
    bool checkheader();
    bool parse(string recv);
    bool separate();
    bool checktail();
};

bool parser::parse(string recv)
{
    if (checkheader()||checktail()) return 1;
    else
    {
        assert(separate()==0);
        switch(dMsgtype)
        {
            case _PLAYER_MOVE:
                broadcastfrom(un,"PM"+strtext);
                break;
            case _BLOCK_CREATE:
                broadcastfrom(un,"BC"+strtext);
                break;
            case _BLOCK_DESTROY:
                broadcastfrom(un,"BD"+strtext);
                break;
            case _NEW_USER:
                if (bexist(un)==1) return 1;
                else addplayer(un);
                break;
            case _SOUND:
                break;              
        }
    }
}

bool parser::separate()
{
    for (int i=0;i<strRecv.length();i++)
    {
        if (strRecv[i]==" ")
        {
            un=str
        }
    }
}