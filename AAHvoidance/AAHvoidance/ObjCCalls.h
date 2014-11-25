//PrintMessage.h
#ifndef __PRINTMESSAGE_H__
#define __PRINTMESSAGE_H__

#include <stddef.h>

class ObjCCalls
{
public:
    void AuthenLocalPlayer();
    void ShowLeaderboard();
    void ReportScore(int score);
    
    void StartSession();
    void FullScreenAdd();
    void LinkAdd();
};

#endif//__PRINTMESSAGE_H__