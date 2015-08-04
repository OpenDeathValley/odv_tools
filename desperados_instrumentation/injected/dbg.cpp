#include "dbg.h"

VOID MakeConsole(VOID)
{
    DWORD dwMode;
    struct _CONSOLE_SCREEN_BUFFER_INFO sbi;
    HANDLE hStd;
    FILE *fStream;

    if (!AllocConsole()) {
        FreeConsole();
        if (!AllocConsole()) {
            dbg_msg("[+] AllocConsole() failed : %lu\n", GetLastError());
        }
    }
    hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStd, (LPDWORD)&dwMode);
    SetConsoleMode(hStd, dwMode & 0xFFFFFFEF);
    GetConsoleScreenBufferInfo(hStd, &sbi);
    sbi.dwSize.Y = 500;
    SetConsoleScreenBufferSize(hStd, sbi.dwSize);
    freopen_s(&fStream, "conin$", "r", stdin);
    freopen_s(&fStream, "conout$", "w", stdout);
    freopen_s(&fStream, "conout$", "w", stderr);
}

VOID dbg_msg(LPCSTR szFormat, ...)
{
    static INT iInit = 0;
    CHAR cpBuffer[512];
    va_list args;
    FILE *fFp = NULL;

    va_start(args, szFormat);
    memset(cpBuffer, 0, sizeof (cpBuffer));
    vsprintf_s(cpBuffer, 512, szFormat, args);
    if (!iInit) {
        fopen_s(&fFp, FILE_DBG, "w");
        iInit = 1;
    }
    else {
        fopen_s(&fFp, FILE_DBG, "a");
    }
    va_end(args);
    if (fFp != NULL) {
        fprintf(fFp, "%s", cpBuffer);
        fclose(fFp);
    }
    printf("%s", cpBuffer);
}

VOID hexdump(PVOID *data, int size)
{
    unsigned char *p = (unsigned char*)data;
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[16 * 3 + 5] = {0};
    char charstr[16 * 1 + 5] = {0};

    for (n = 1; n <= size; n++) {
        if (n % 16 == 1) {
            sprintf_s(addrstr, sizeof(addrstr), "%.4x", ((unsigned int)p - (unsigned int)data));
        }
        c = *p;
        if (isprint(c) == 0) {
            c = '.';
        }
        sprintf_s(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat_s(hexstr, sizeof(hexstr), bytestr, sizeof(hexstr) - strlen(hexstr) - 1);
        sprintf_s(bytestr, sizeof(bytestr), "%c", c);
        strncat_s(charstr, sizeof(charstr), bytestr, sizeof(charstr) - strlen(charstr) - 1);
        if (n % 16 == 0) {
            dbg_msg("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
            hexstr[0] = 0;
            charstr[0] = 0;
        }
        else if (n % 8 == 0) {
            strncat_s(hexstr, sizeof(hexstr), "  ", sizeof(hexstr)-strlen(hexstr)-1);
        }
        p++;
    }
    if (strlen(hexstr) > 0) {
        dbg_msg("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
    }
}
