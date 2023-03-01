#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define READ_END 0
#define WRITE_END 1

int print(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	return (1);
}

int bulitin_cd(char *path, int i)
{
	if (i > 2)
		return (print("error: cd: bad arguments\n"));
	
}

int main(int ac, char **av, char **envp)
{
	int i = 1;

	if (ac < 2)
		return (1);
	while (av[i - 1] && av[i])
	{
		av = av + i;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (i == 0)
			break;
		if (strcmp(av[0], "cd") == 0)
			bulitin_cd(av[1], i);
		else
			executor(av, i, envp);
		i++;
	}
	return (0);
}