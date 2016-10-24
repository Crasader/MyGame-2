//
//  AudioManager.h
//  BullPoker
//
//  Created by 陈冬梅 on 2016/10/23.
//
//

#ifndef AudioManager_h
#define AudioManager_h

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class AudioManager{
public:
    static AudioManager* getInstance();
    void fileConvertedToBinary_Send(const char* filePath);
    void binaryConvertedToFile_Rev(const char* filePath,const char* binaryData,long length);
    char* data;
    long length;
};



#endif /* AudioManager_h */