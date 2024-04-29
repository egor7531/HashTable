#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdio.h>

struct File
{
    FILE* fp;
    char* buf;
    int sizeFile;
    char** words;
    int nWords;
};

File* file_ctor(const char* nameFile);
void  file_dtor(File* file);

#endif // FILE_H_INCLUDED
