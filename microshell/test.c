#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define READ_END 0
#define WRITE_END 1

static int	print(char *str)
{
	int	i = 0;
	while (str[i]) i++;
	write(2, str, i);
	return (1);
}

static int	builtin_cd(char *path, int i)
{
	if (i > 2)
		return (print("error: cd: bad arguments\n"));
	if (chdir(path) == -1)
	{
		print("error: cd: cannot change directory to ");
		print(path);
		return (print("\n"));
	}
	return (0);
}

static int	executor(char **argv, int i, char **envp)
{
	int	pipe_fd[2];
	int	is_next = 0;
	int	pid = 0;
	int	status = 0;
	static int	prev_fd;

	if (argv[i] && strcmp(argv[i], "|") == 0)
		is_next = 1;
	pipe(pipe_fd);
	if (prev_fd != 0)
	{
		dup2(prev_fd, STDIN);
		close(prev_fd);
	}
	pid = fork();
	if (pid == -1)
	{
		print("error: fatal\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (is_next == 1)
			dup2(pipe_fd[WRITE_END], STDOUT);
		close(pipe_fd[READ_END]);
		close(pipe_fd[WRITE_END]);
		argv[i] = NULL;
		int j = 0;
		while(argv[j])
		{
			printf("%s\n", argv[j]);
			j++;
		}
		if (execve(argv[0], argv, envp) == -1)
		{
			print("error: cannot execute ");
			print(argv[0]);
			print("\n");
			exit(1);
		}
	}
	waitpid(pid, &status, 0);
	if (is_next == 1)
		prev_fd = dup(pipe_fd[READ_END]);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i = 1;

	if (argc < 2)
		return (1);
	while (argv[i - 1] && argv[i])
	{
		argv = argv + i;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i == 0)
		{	
			i++;
			continue;
		}
		if (strcmp(argv[0], "cd") == 0)
			builtin_cd(argv[1], i);
		else
		{
			executor(argv, i, envp);
		}
		i++;
	}
	return (0);	
}