#include "minishell.h"

static int		run_fork(char *path, char **av, char **env)
{
	pid_t		pid;

	pid = fork();
	signal(SIGINT, process_signal_handler);
	if (pid == 0)
		execve(path, av, env);
	else if (pid < 0)
	{
		free(path);
		ft_putendl("Fork failed to create process");
		return (-1);
	}
	wait(&pid);
	free(path);
	return (1);
}

static int		check_builtins(char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		return (-1);
/*	else if (!ft_strcmp(cmd[0], "cd"))
		return (cd_builtin(cmd + 1));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo_builtin(cmd + 1));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(cmd + 1));
	else if (!ft_strcmp(cmd[0], "unsetenv))
		return (echo_builtin(cmd + 1));
	else if (!ft_strcmp(*av, "env"))
	{
		while (*env)
			my_printf("%s\n", env[i++]);
	}*/
	return (0);
}

char			**walking_path(char **env, char *str)
{
	char		**tab;
	int		i;
	int		len;

	tab = NULL;
	i = 0;
	while (env[i++])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		if (!ft_strncmp(str, env[i], len))
		{
			tab = ft_strsplit(env[i] + len + 1, ':');
			break ;
		}
	}
	return (tab);
}

static int		find_builtin(char **cmd, char **env)
{
	char		**path;
	char		*abs_path;
	int		i;
	struct stat	fd;

	i = 0;
	path = walking_path(env, "PATH");
	while (path && path[i++])
	{
		abs_path = ft_strjoin(path[i], "/");
		abs_path = ft_strjoin(abs_path, cmd[0]);
		if (lstat(abs_path, &fd) == -1)
			free(abs_path);
		else
			return (run_fork(abs_path, cmd, env));
	}
	return (0);
}

int			exec_cmd(char **cmd, char **env)
{
	struct stat	fd;
	int		ret;

	if ((ret = check_builtins(cmd)) == -1)
		return (-1);
	if (find_builtin(cmd, env))
		return (0);
	if (lstat(cmd[0], &fd) != -1)
	{
		if (fd.st_mode & S_IXUSR)	
			return (run_fork(ft_strdup(cmd[0]), cmd, env));
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(cmd[0]);
	return (0);
}
