
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/wait.h>

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

static int	execute_command(t_command *cmd, char **envp)
{
	int	pid;

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
			print_error("microshell: Error execve\n");
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
		waitpid(pid, 0, 0);
	}

	return 0;
}

static int	cd_command(t_command *cmd)
{
	if (strcmp(cmd->bin, "cd") || !(cmd->args[1]) || (cmd->args[2]))
		return 1;
	if (chdir(cmd->args[1]) == -1)
		print_error("microshell: error: cd\n");
	return 0;
}

static void	init_pipe(t_command *cmd)
{
	if (!(cmd->isPipe))
		return ;
	if (pipe(cmd->fd) == -1)
	{
		print_error("microshell: error: pipe\n");
		exit(1);
	}
}

static void	find_command(char ***arguments, t_command *cmd)
{
	int	index;

	index = 0;
	while ((*arguments)[index]
		&& strcmp((*arguments)[index], ";")
		&& strcmp((*arguments)[index], "|"))
		++index;
	if ((*arguments)[index] == 0)
	{
		*arguments = &((*arguments)[index]);
		return ;
	}
	if (!strcmp((*arguments)[index], "|"))
		cmd->isPipe = 1;
	(*arguments)[index] = 0;
	*arguments = &((*arguments)[index + 1]);
}

static int	microshell(char **arguments, char **envp)
{
	t_command	cmd;

	while (*arguments)
	{
		cmd.isPipe = 0;
		cmd.bin = *arguments;
		cmd.args = arguments;
		find_command(&arguments, &cmd);
		init_pipe(&cmd);
		if (cd_command(&cmd))
			execute_command(&cmd, envp);
	}

	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return 0;

	++argv;

	return microshell(argv, envp);
}
