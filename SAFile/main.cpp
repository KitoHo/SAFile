//
//  main.cpp
//  SAFile
//
//  Created by StellaKito on 8/6/2015.
//  Copyright (c) 2015年 KitoHo. All rights reserved.
//

#include <unistd.h>
#include <iostream>
using namespace std;

#include "SAFile.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    char path[PATH_MAX] = {0};
    getcwd(path, PATH_MAX);
    
    cout << path << endl;
    //SAFile file("/Users/kito/Desktop/Xcode_Project/SAFile/arc.sa");
    //file.addFile("/Users/kito/Desktop/Xcode_Project/SAFile/files/mzl.oizkymla.200x200-75.png");
    //file.addFile("/Users/kito/Desktop/Xcode_Project/SAFile/files/mzl.ozzgribk.200x200-75.png");
    //file.addFile("/Users/kito/Desktop/Xcode_Project/SAFile/files/mzl.rltchoit.200x200-75.png");
    //file.archive();
    
    SAFile file("/Users/kito/Desktop/Xcode_Project/SAFile/arc2.sa");
    file.addFile("/Users/kito/Desktop/Xcode_Project/SAFile/files/mzl.vudxrzja.200x200-75.png");
    file.addFile("/Users/kito/Desktop/Xcode_Project/SAFile/files/mzl.ylxiprpt.200x200-75.png");
    file.archive();
    
    vector<FileRecord> record;
    file.getFileList(&record);
    cout << "File Count : " << record.size() << endl;
    for (int i = 0; i < record.size(); i++)
    {
        cout << record.at(i).path << endl;
    }
    
    return 0;
}
