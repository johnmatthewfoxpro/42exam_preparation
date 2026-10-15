#include <stdio.h>
#include <stdlib.h>

void print_subset(int *set, int *chosen, int length)
{
	int i = 0;
	int first = 1;

	while (i < length)
	{
		if (chosen[i])
		{
			if (!first)
				printf(" ");
			printf("%d", set[i]);
			first = 0;
		}
		i++;
	}
	printf("\n");
}

void powerset(int *set, int *chosen, int length, int index, int target, int sum)
{
	if (index == length)
	{
		if (sum == target)
			print_subset(set, chosen, length);
		return;
	}
	chosen[index] = 0;
	powerset(set, chosen, length, index + 1, target, sum);
	chosen[index] = 1;
	powerset(set, chosen, length, index + 1, target, sum + set[index]);

	chosen[index] = 0;
}

int main(int argc, char **argv)
{
	int target;
	int length;
	int *set;
	int *chosen;
	int i = 0;

	if (argc <= 2 || (argc >= 2 && argv[1][0] == '0' && argv[1][1] == '\0'))
	{
		printf("\n");
		return 1;
	}

	target = atoi(argv[1]);
	length = argc - 2;

	set = malloc((length + 1) * sizeof(int));
	chosen = calloc(length + 1, sizeof(int));
	if (!set || !chosen)
	{
		free(set);
		free(chosen);
		return (1);
	}

	while (i < length)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}

	powerset(set, chosen, length, 0, target, 0);

	free(set);
	free(chosen);
	return (0);
}
