#include <stddef.h>
#include <stdint.h>

int 
mkdir(const char *dirname);

int 
exists(const char *path);

char *
getcwd(char *dir, int size);

int
chdir(const char *path);

int64_t
mtime(const char *path);

int64_t
now(void);

void proc_spawn(void);
