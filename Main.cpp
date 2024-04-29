#include <stdio.h>
#include "File.h"
#include <string.h>

const char* nameFile = "Christie Agatha . And Then There Were None - royallib.ru.txt";
const char* nameFile1 = "data.txt";

int main()
{
    File* file = file_ctor(nameFile1);
    for(int i = 0; i < file->sizeFile; i++)
    {
        printf("%d ", file->buf[i]);
    }
    file_dtor(file);
    return 0;
}