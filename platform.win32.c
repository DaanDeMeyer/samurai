#define _WIN32_WINNT _WIN32_WINNT_VISTA
#include <sys/stat.h>
#include <windows.h>
#include <direct.h>
#include "platform.h"

int 
mkdir(const char *dirname)
{
    return _mkdir(dirname);
}

int
exists(const char *path)
{
    struct _stat st;
    return _stat(path, &st) == 0;
}

char *
getcwd(char *dir, int size)
{
    return _getcwd(dir, size);
}

int
chdir(const char *path)
{
    return _chdir(path);
}

int64_t
mtime(const char *path)
{
    struct _stat st;
    
    int r = _stat(path, &st);

    return r < 0 ? r : (int64_t) st.st_mtime * 1000000000;
}

int64_t reproc_now(void)
{
  return (int64_t) GetTickCount64() / 1000;
}
