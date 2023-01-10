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

static void	print_error(char *error)
{
	while (*error)
		write(2, error++, 1);
}

static void find_command(char ***arg, t_command *cmd)
{
	int i = 0;

	while ((*arg)[i] != 0 && strcmp((*arg)[i], ";") && strcmp((*arg)[i], "|"))
		i++;
	if ((*arg)[i] == 0)
	{
		*arg = &((*arg)[i]);
		return ;
	}
	if (!strcmp((*arg)[i], "|"))
	{
		cmd->isPipe = 1;
	}
	(*arg)[i] = 0;
	*arg = &((*arg)[i + 1]);
}

static void init_pipe(t_command *cmd)
{
	if (!(cmd->isPipe))
		return ;
	if (pipe(cmd->fd) == -1)
	{
		print_error("microshell: error: there's no pipe\n");
		exit(1);
	}
}

static int cd_command(t_command *cmd)
{
	if (strcmp(cmd->bin, "cd") || !(cmd->args[1]) || !(cmd->args[0]))
		return (1);
	if (chdir(cmd->args[1]) == -1)
		print_error("microshell: error: cd\n");
	return (0);
}

static void	execute_command(t_command *cmd, char **envp)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->isPipe)
		{
			dup2(cmd->fd[1], 1);
			close(cmd->fd[1]);
			close(cmd->fd[0]);
		}
		if (execve(cmd->bin, cmd->args, envp) == -1)
		{
			print_error("microshell: error: execve");
			exit(1);
		}
	}
	else
	{
		if (cmd->isPipe)
		{
			dup2(cmd->fd[0], 0);
			close(cmd->fd[0]);
			close(cmd->fd[1]);
		}
		waitpid(pid, 0 ,0);
	}
}

static int microshell(char **args, char **envp)
{
	t_command cmd;

	while (*args)
	{
		cmd.isPipe = 0;
		cmd.bin = *args;
		cmd.args = args;
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
