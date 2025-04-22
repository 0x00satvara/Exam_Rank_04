#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

int picoshell(char **cmds[])
{
    int res = 0;
    int pr_fd = -1;
    pid_t pid;
    int i = 0;
    int fd[2];
    int sta;
    while (cmds[i])
    {
        if(cmds[i + 1])
            pipe(fd);
        pid = fork();
        if( pid == -1)
            return 1;
        if (!pid)
        {
            if(pr_fd != -1)
            {
                dup2(pr_fd, 0);
                close(pr_fd);
            }
            if(cmds[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            return 1;
        }

        while (wait(&sta) == -1)
        {
            if(WIFEXITED(sta) && WEXITSTATUS(sta) != 0)
                res = 1;
        }

        if(pr_fd != -1)
            close(pr_fd);

        if(cmds[i + 1])
        {
            close(fd[1]);
            pr_fd = fd[0];
        }
        i++;
    }
    return res;
}
