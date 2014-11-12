#ifndef OPENDV_FILE_H
#define OPENDV_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <windows.h>

// cmake
// CHECK_FUNCTION_EXISTS(_fileno HAVE__FILENO)
// #cmakedefine HAVE__FILENO

#if defined(HAVE__FILENO)
#define fileno _fileno
#endif

struct ODVFile
{
    char filename[FILENAME_MAX];
    unsigned char *buf;
    unsigned int length;
    unsigned int pos;

    /* WINDOWS */
    HANDLE file;
    HANDLE map;
};

struct ODVFile *odv_file_open(char *filename);
void odv_file_info(struct ODVFile *file);
int odv_file_read(struct ODVFile *file, void *buf, size_t count);
int odv_file_readline(struct ODVFile *file, void *buf, size_t count);
void odv_file_seek(struct ODVFile *file, unsigned int offset);
int odv_file_close(struct ODVFile *file);

struct ODVFile *odv_file_open_win(char *filename);
int odv_file_close_win(struct ODVFile *file);

#endif /* OPENDV_FILE_H */
