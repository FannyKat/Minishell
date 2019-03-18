/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:24:17 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/18 17:42:57 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		run_fork(char *path, char **av, char **env)
{
	pid_t		pid;
	
	pid = fork();
	signal(SIGINT, process_signal_handler);
	if (pid == 0)
	{
		if (execve(path, av, env) == -1)
			ft_putendl_fd("not an executable", 2);
	}
	else if (pid < 0)
	{
		free(path);
		ft_putendl_fd("Fork failed to create process", 2);
		return (-1);
	}
	wait(&pid);
	free(path);
	return (1);
}

static int		check_builtins(char **cmd, char **env)
{
	if (!ft_strcmp(cmd[0], "exit"))
		return (-1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo_builtin(cmd + 1));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(cmd + 1, env));	
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (unsetenv_builtin(cmd + 1, env));
/*	else if (!ft_strcmp(cmd[0], "cd"))
		return (cd_builtin(cmd + 1));
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
	int			i;
	int			len;

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
	struct stat	fd;
	char		**path;
	char		*abs_path;
	int			i;

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

int				exec_cmd(char **cmd, char **env)
{
	struct stat	fd;

	if (check_builtins(cmd, env) || find_builtin(cmd, env))
		return (0);
	if (check_builtins(cmd, env) == -1)
		return (-1);
	if (lstat(cmd[0], &fd) != -1)
	{
		if (fd.st_mode & S_IXUSR)	
			return (run_fork(ft_strdup(cmd[0]), cmd, env));
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(cmd[0]);
	}
	return (0);
}
