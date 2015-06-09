//
//  SAFile.h
//
//
//  Created by Kito on 7/6/2015.
//  Copyright (c) 2015年 Kito. All rights reserved.
//

#ifndef _SAFILE_H_
#define _SAFILE_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <vector>
using namespace std;

typedef const char      cchar;
typedef unsigned int    uint;
typedef unsigned long   ulong;

typedef struct _SAFileHeader
{
    char identify[5];
    uint count;
    ulong size;
} SAFileHeader;

typedef struct _SAFileRecord
{
    char* path;
    ulong idx;
    ulong len;
} SAFileRecord;

typedef struct _FileRecord
{
    uint fid;
    cchar* path;
} FileRecord;

class SAFile
{
    private:
        cchar* _path;
        ulong _tmpSize;
        SAFileHeader _header;
        vector<SAFileRecord> _todos;
        vector<SAFileRecord> _records;
        bool _isSAFile;
    
    public:
        SAFile(cchar* file);
        ~SAFile();
    
        void addFile(cchar* path);
    
        void getFile(cchar* path, cchar** bytes, ulong* len);
        void getFileList(vector<FileRecord>* files);
    
        void archive(void);
};

#endif /* defined(__TestProject__SAFile__) */
