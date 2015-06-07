//
//  SAFile.cpp
//  
//
//  Created by Kito on 7/6/2015.
//  Copyright (c) 2015年 Kito. All rights reserved.
//

#include "SAFile.h"

#define BUFFER_SIZE 2048

SAFile::SAFile(cchar* file)
{
    _path = strdup(file);
    
    strcpy(_header.identify, "SA00");
    _header.count = 0;
    _header.size = 0;
    
    // todo append file path
    _isSAFile = true;
    if (FILE* f = fopen(_path, "rb+"))
    {
        char identify[3] = {0};
        fread(identify, sizeof(char), 2, f);
        _isSAFile = (strcmp(identify, "SA") == 0);
        
        if(_isSAFile)
        {
            rewind(f);
            fread(&_header, sizeof(SAFileHeader), 1, f);
            
            char* buffer = new char[_header.size];
            memset(buffer, 0, _header.size);
            fread(buffer, sizeof(char), _header.size, f);
            
            char* ptr = buffer;
            for (int i = 0; i < _header.count; i++)
            {
                SAFileRecord record;
                
                size_t len = strlen(ptr) + 1;
                record.path = new char[len];
                memset(record.path, 0, len);
                strncpy(record.path, ptr, len);
                ptr += len;
                
                record.idx = *((unsigned long*)ptr);
                ptr += sizeof(ulong);
                
                record.len = *((unsigned long*)ptr);
                ptr += sizeof(ulong);
                //printf("%s : %ld : %ld\n", record.path, record.idx, record.len);
                
                _records.push_back(record);
            }
            
            delete[] buffer;
        }
        
        fclose(f);
    }
    else
    {
        _isSAFile = false;
    }
}

SAFile::~SAFile()
{
    delete _path;
}

void SAFile::addFile(cchar* path)
{
    SAFileRecord record;
    record.path = strdup(path);
    record.idx = 0;
    record.len = 0;
    _todos.push_back(record);
    
    _tmpSize += strlen(path) + 1;
}

void SAFile::getFile(cchar* path, cchar** bytes, ulong* len)
{
    
}

void SAFile::archive(void)
{
    FILE* tf = tmpfile();
    ulong head = 0;
    char buffer[BUFFER_SIZE] = {0};
    int fcnt = (int)_todos.size();
    while (!_todos.empty())
    {
        SAFileRecord record = _todos.front();
        _todos.erase(_todos.begin());
        
        FILE* inf = fopen(record.path, "rb+");
        size_t len = 0;
        while((len = fread(buffer, 1, BUFFER_SIZE, inf)))
        {
            fwrite(buffer, 1, len, tf);
            record.len += len;
        }
        fclose(inf);
        
        record.idx = head;
        head += record.len;
        //printf("%s : %ld : %ld\n", record.path, record.idx, record.len);
        
        _records.push_back(record);
    }
    rewind(tf);
    
    FILE* f = fopen(_path, "wb+");

    _header.count += fcnt;
    _header.size += _tmpSize + ((sizeof(ulong) * 2) * fcnt);
    fwrite(&_header, sizeof(SAFileHeader), 1, f);
    
    for (int i = 0; i < _records.size(); i++)
    {
        SAFileRecord record = _records.at(i);
        fwrite(record.path, sizeof(char), strlen(record.path) + 1, f);
        fwrite(&record.idx, sizeof(ulong), 1, f);
        fwrite(&record.len, sizeof(ulong), 1, f);
    }
    
    size_t len = 0;
    while((len = fread(buffer, 1, BUFFER_SIZE, tf)))
    {
        fwrite(buffer, 1, len, f);
    }
    
    fclose(tf);
    fclose(f);
}