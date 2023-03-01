#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STDIN 0 
#define STDOUT 1
#define STDERR 2

#define READ_END 0
#define WRITE_END 1

int print(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	write(2,str,i);
	return 1;
}


int bulitin_cd(char *path, int i)
{
	if (i > 2)
	{
		return(print("error: cd: bad arguments\n"));
	}
	if (chdir(path) == -1)
	{
		print("error: cd: cannot change directory to ");
		print(path);
		return (print("\n"));
	}
	return (0);
}

// ===========================================================
int excute_cmd(char **av, int i, char **envp)
{
	int pid = 0;
	int status = 0;
	int is_next = 0;
	int pipe_fd[2];
	static int prev_fd;

	if (av[i] && strcmp(av[i], "|") == 0)
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
		if(is_next == 1)
			dup2(pipe_fd[WRITE_END], STDOUT);
		close();
		close();
		av[i] == NULL;
		if (execve() == -1)
		{
			print();
			exit(1);
		}
	}
	waitpid(pid, &status, 0);
	if (is_next == 1)
		prev_fd = dup(pipe_fd[READ_END]);
	close
	close
	return 0;

}

// ==============================================

int main(int ac, char **av, char **envp)
{
	int i = 1;

	if (ac < 2)
		return 1;
	while (av[i - 1] && av[i])
	{
		av = av + i;
		i = 0;

		while (av[i] && strcmp(av[i], "|")== 0 && strcmp(av[i], ";"))
			i++;
		if (i == 0)
			break;
		
		if (strcmp(av[0], "cd") == 0)
			bulitin_cd(av[1], i);
		else
			excute_cmd(av, i, envp);
		i++;
	}	
	return 0;
}

//==================================================


int main(int ac, char **av, char **envp)
{
	int i = 1;

	if (ac < 2)
		reutrn 1;
	while(av[i -1] && av[i])
	{
		av = av + i;

		i = 0;

		while(av[i], strcmp(av[i]))
	}
}