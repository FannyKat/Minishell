/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:24:17 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 18:24:16 by fcatusse         ###   ########.fr       */
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
			ft_putendl_fd("Not an executable", 2);
		exit(0);
	}
	else if (pid < 0)
	{
		ft_strdel(&path);
		ft_putendl_fd("Fork failed to create process", 2);
		return (-1);
	}
	else if (pid > 0)
		wait(&pid);
	ft_strdel(&path);
	return (1);
}

static int		check_builtins(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "exit"))
		return (-1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo_builtin(cmd + 1, env));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(cmd + 1, env));	
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (unsetenv_builtin(cmd + 1, env));	
	else if (!ft_strcmp(cmd[0], "cd"))
		return (cd_builtin(cmd + 1, env));
	else if (!ft_strcmp(cmd[0], "env"))
	{
		print_tab(*env);
		return (1);
	}
	return (0);
}

char			**walking_path(char **env, char *str)
{
	char		**tab;
	int			i;
	int			len;

	tab = NULL;
	i = -1;
	while (env[++i])
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
	char		*tmp;

	i = -1;
	path = walking_path(env, "PATH");
	while (path && path[++i])
	{
		abs_path = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(abs_path, cmd[0]);
		ft_strdel(&abs_path);
		abs_path = tmp;
		if (lstat(abs_path, &fd) == -1)
			ft_strdel(&abs_path);
		else
			return (run_fork(abs_path, cmd, env));
	}
	return (0);
}

int				exec_cmd(char **cmd, char ***env)
{
	struct stat	fd;
	
	if (check_builtins(cmd, env) || find_builtin(cmd, *env))
		return (0);
	if (check_builtins(cmd, env) == -1)
		return (-1);
	if (lstat(cmd[0], &fd) != -1)
	{
		if (fd.st_mode & S_IXUSR)
			return (run_fork(ft_strdup(cmd[0]), cmd, *env));
	}
	else
	{
		ft_putstr("Minishell: command not found: ");
		ft_putendl(cmd[0]);
	}
	return (0);
}
