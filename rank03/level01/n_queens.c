#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int absol(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

int is_safe(int *board, int row, int col)
{
	int i = 0;

	while (i < row)
	{
		if (board[i] == col)
			return (0);
		if(absol(board[i] - col) == absol(i - row))
			return (0);
		i++;
	}
	return (1);
}

void n_queen(int *board, int n, int row)
{
	int i = 0;
	char c;

	if (row == n)
	{
		while (i < n)
		{
			c = board[i] + '0';
			write(1, &c, 1);
			if (i != n - 1)
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
		return ;
	}
	while (i < n)
	{
		if (is_safe(board, row, i))
		{
			board[row] = i;
			n_queen(board, n, row + 1);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	int n = atoi(argv[1]);
	int row = 0;
	int *board = malloc(n * sizeof(n));

	if (!board)
		return (1);
	n_queen(board, n, row);
	free(board);
	return (0);
}