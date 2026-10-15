#include "get_next_line.h"

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

