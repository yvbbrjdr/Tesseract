#include "afx.h"
vector<string> playerlist;
bool bexist(string un)
{
    for (int t=0;t<playerlist.size();t++)
        if (playerlist[t]==un) return 1;
    return 0;
}
bool addplayer(string un)
{
    if (bexist(un)==1) return 1;
    else{
        playerlist.push_pack(un);
        return 0;
    }
}
bool removeplayer(string un);
{
    vector<string>::iterator ite;
    for (ite=playerlist.begin();ite!=playerlist.end();)
    {
        if(*ite==un)
        {
            ite=playerlist.erase(ite);
            return 0;
        }
        else
            ++ite;
    }
    return 1;
}
