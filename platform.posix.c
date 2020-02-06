#define _POSIX_C_SOURCE 200809L
#include <sys/stat.h>
#include "platform.h"

int
mkdir(const char *dirname)
{
    return mkdir(dirname, 0777);
}

int
exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

int64_t
now(void)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec + 0.000000001 * time.tv_nsec;
}

void proc_start(void)
{
    int fd[2];
    posix_spawn_file_actions_t actions;
    char *argv[] = {"/bin/sh", "-c", NULL, NULL};

    if (pipe(fd) < 0) {
		warn("pipe:");
		goto err1;
	}

    j->fd = fd[0];

    if ((errno = posix_spawn_file_actions_init(&actions))) {
		warn("posix_spawn_file_actions_init:");
		goto err2;
	}
	if ((errno = posix_spawn_file_actions_addclose(&actions, fd[0]))) {
		warn("posix_spawn_file_actions_addclose:");
		goto err3;
	}
	if (e->pool != &consolepool) {
		if ((errno = posix_spawn_file_actions_addopen(&actions, 0, "/dev/null", O_RDONLY, 0))) {
			warn("posix_spawn_file_actions_addopen:");
			goto err3;
		}
		if ((errno = posix_spawn_file_actions_adddup2(&actions, fd[1], 1))) {
			warn("posix_spawn_file_actions_adddup2:");
			goto err3;
		}
		if ((errno = posix_spawn_file_actions_adddup2(&actions, fd[1], 2))) {
			warn("posix_spawn_file_actions_adddup2:");
			goto err3;
		}
		if ((errno = posix_spawn_file_actions_addclose(&actions, fd[1]))) {
			warn("posix_spawn_file_actions_addclose:");
			goto err3;
		}
	}
	if ((errno = posix_spawn(&j->pid, argv[0], &actions, NULL, argv, environ))) {
		warn("posix_spawn %s:", j->cmd->s);
		goto err3;
	}
	posix_spawn_file_actions_destroy(&actions);
	close(fd[1]);

err3:
	posix_spawn_file_actions_destroy(&actions);
err2:
	close(fd[0]);
	close(fd[1]);

    return -1;
}
