#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

void ft_sort(char *str, int len)
{
	int i = 0;
	char tmp;

	while (i < len - 1)
	{
		if (str[i] > str[i + 1])
		{
			tmp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void recu_permut(char *str, char * solution, int length, int position, int *used)
{
	int i = 0;

	if (position == length)
	{
		puts(solution);
		return ;
	}

	while (i < length)
	{
		if (!used[i])
		{
			solution[position] = str[i];
			used[i] = 1;
			recu_permut(str, solution, length, position + 1, used);
			used[i] = 0;
		}
		i++;
	}
}

void permut(char *str)
{
	int position = 0;
	int length = ft_strlen(str);
	int *used;
	char *solution;

	used = malloc(length * sizeof(int));
	if (!used)
		return ;
	while (position < length)
	{
		used[position] = 0;
		position++;
	}
	position = 0;
	solution = malloc((length * sizeof(char)) + 1);
	if (!solution)
	{
		free(used);
		return ;
	}
	solution[length] = '\0';
	ft_sort(str, length);
	recu_permut(str, solution, length, position, used);
	free(used);
	free(solution);
}

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	permut(argv[1]);
	return (0);
}