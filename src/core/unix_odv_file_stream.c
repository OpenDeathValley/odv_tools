#include "ODVFile.h"

struct ODVFile *odv_file_open(char *filename)
{
    return NULL;
}

int odv_file_read(struct ODVFile *file, void *buf, size_t count)
{
    /* TODO */
}

int odv_file_readline(struct ODVFile *file, char *buf, size_t count)
{
    /* TODO */
}

void odv_file_seek(struct ODVFile *file, unsigned int offset)
{
    /* TODO */
}

int odv_file_close(struct ODVFile *file)
{
    /* TODO */
}

int odv_file_close_win(struct ODVFile *file)
{
    /* TODO */
}

void odv_file_info(struct ODVFile *file)
{
    if (file == NULL)
        return;
    printf("[- ODV file information -]\n");
    printf("filename : %s\n", file->filename);
    printf("filesize : 0x%08X\n", file->length);
    printf("position : 0x%08X\n", file->pos);
    printf("[------------------------]\n");
}
