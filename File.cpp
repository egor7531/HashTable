#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>

#include "File.h"

int get_file_size(FILE* fp)
{
    assert(fp != nullptr);

    struct stat st;
    fstat(fileno(fp), &st);
    return st.st_size;
}

void file_read(File* file)
{
    assert(file != nullptr);

    if(fread(file->buf, sizeof(char), file->sizeFile, file->fp) != file->sizeFile)
    {
        if(feof(file->fp))
            printf("Premature end of file\n");
        else
            printf("File read error\n");
    }
}

int skip_spaces(File* file, int index)
{
    assert(file != nullptr);
    assert(index >= 0);

    char ch = file->buf[index];
    while( (ch == ' ' || ch == '\n' || ch == '\r') && index < file->sizeFile)
    {
        index++;
        ch = file->buf[index];
    }

    return index;
}

int get_number_words(File* file)
{
    assert(file != nullptr);

    int nWords = 0;
    int i = 0;
    i = skip_spaces(file, i);
    for( ; i < file->sizeFile; i++)
    {
        char ch = file->buf[i];
        if(i == file->sizeFile - 1)
        {
            nWords++;
            break;
        }
        if(ch == ' ' || ch == '\n' || ch == '\r')
        {   
            i = skip_spaces(file, i) - 1;
            nWords++;
        }
    }

    return nWords;
}

char** get_pointers_words(File* file)
{
    assert(file != nullptr);

    int nWords = get_number_words(file);
    char** words = (char**)calloc(nWords, sizeof(char*));
    assert(words != nullptr);

    int j = 0;
    for(int i = 0; i < file->sizeFile; i++)
    {
        i = skip_spaces(file, i);
        bool flag = true;
        while( 'A' <= file->buf[i] && file->buf[i] <= 'Z' || 'a' <= file->buf[i] && file->buf[i] <= 'z' || file->buf[i] == '\'') 
        {
            if(flag)
            {
                words[j] = file->buf + i;
                j++;
                flag = false;
            }
            file->buf[i] = tolower(file->buf[i]);
            i++;
        }
        file->buf[i] = '\0';
    }
    file->nWords = j;

    return words;
}

File* file_ctor(const char* nameFile)
{
    assert(nameFile != nullptr);

    File* file = (File*)calloc(1, sizeof(File));
    assert(file != nullptr);
    
    FILE* fp = fopen(nameFile, "rb");
    assert(fp != nullptr);

    file->fp = fp;

    file->sizeFile = get_file_size(fp);
    file->buf = (char*)calloc(file->sizeFile, sizeof(char));
    assert(file->buf != nullptr);
    file_read(file);

    file->nWords = get_number_words(file);
    file->words = get_pointers_words(file);

    return file;
}

void file_dtor(File* file)
{
    assert(file != nullptr);

    free(file->buf);
    free(file->words);
    fclose(file->fp);
}
