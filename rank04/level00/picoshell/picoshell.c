#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int    picoshell(char **cmds[])
{
    pid_t pid;  // for fork
    int fd[2];   // for the current pipe
    int last_fd = -1;  //to store the previous pipe' read end
    int i = 0;    // index for looping through cmds

    while(cmds[i])   // loop run until null
    {
        if(cmds[i + 1] && pipe(fd) == -1)   // create a pipe for the next command
            return 1;
        pid = fork();   //create a child process
        if(pid == -1)    //if fork fails
        {
            if(cmds[ i+ 1])  // if a pipe was created, close it
            {
                close(fd[0]);
                close(fd[1]);
            }
            return 1; // return with error
        }
        if(pid == 0)  //inside child process
        {
            if(last_fd != -1)    //if not the first command, set up input from previous pipe
            {
                if(dup2(last_fd, STDIN_FILENO) == -1)  //dup2 fails
                    exit(1);   //exit child with error
                close(last_fd);    //close the read end after duplicating
            }
            if(cmds[i + 1])   //if not the last command, set up output to the current pipe
            {
                close(fd[0]);   //close the read end of the current pipe
                if(dup2(fd[1], STDOUT_FILENO) == -1)  //dup2 fails
                    exit(1); //exit child with error
                close(fd[1]); //close the write end after duplicating
            }
            execvp(cmds[i][0], cmds[i]);  //execute the command
            exit(1); //if execvp fails, exit child with error
        }
        if(last_fd != -1)   //if not the first command, close the previous pipe's read end
            close(last_fd);  // it's no longer needed in the parent
        if(cmds[i + 1])  // if there is a next command
        {
            close(fd[1]); // close the write end of the current pipe in the parent
            last_fd = fd[0];  // save the read end for the next command
        }
        i++;
    }
    while(wait(NULL) > 0)
    {
    	;
    }
    return(0);
}
