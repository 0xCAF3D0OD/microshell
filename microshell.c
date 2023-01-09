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

static void find_command(char *arg, t_command *cmd)
{
	
}

static int microshell(char **av, char **envp)
{
	t_command *cmd;

	while (*av)
	{
		cmd->isPipe = 0;
		cmd->bin = *av;
		cmd->args = av;
		find_command(&args, &cmd);
		init_pipe(&cmd);
		if (cd_command(&cmd))
			execute_command(&cmd, envp);

	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	if (ac == 1)
		return (0);
	av++;
	return (microshell(av, envp));
}

