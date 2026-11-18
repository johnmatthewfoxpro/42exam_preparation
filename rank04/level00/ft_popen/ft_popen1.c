#ifndef GNL
# define GNL

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

#endif

int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	if (!file || !argv || (type != 'r' && type != 'w') || pipe(fd) < 0)
		return (-1);
	if ((pid = fork()) < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd[type == 'r' ? 1 : 0], type == 'r' ? 1 : 0);
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	close(fd[type == 'r' ? 1 : 0]);
	return (fd[type == 'r' ? 0 : 1]);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int bytes = 0, pos = 0;
	char *line = malloc(1000000), *buf = line;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
	{
		if (line)
			free(line);
		return (NULL);
	}

	while (1)
	{
		if (pos >= bytes)
		{
			pos = 0;
			if ((bytes = read(fd, buffer, BUFFER_SIZE)) <= 0)
				break ;
		}
		*buf = buffer[pos++];
		if (*buf++ == '\n')
			break ;
	}
	if (buf == line)
	{
		free(line);
		return (NULL);
	}
	*buf = '\0';
	return (line);
}

// int	main()
// {
// 	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	dup2(fd, 0);
// 	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
// 	char	*line;
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// }

int main()
{
    int  fd;
    char *line;

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((line = get_next_line(fd)))
        ft_putstr(line);
    return (0);
}
