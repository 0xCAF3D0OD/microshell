#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_command {
	char	*bin;
	char	**args;
	int		isPipe;
	int		fd[2];
}	t_command;

static int microshell(char **av, char **envp)
{
	
	return (0);
}

int main(int ac, char **av, char **envp)
{
	if (ac == 1)
		return (0);
	av++;
	return (microshell(av, envp));
}

