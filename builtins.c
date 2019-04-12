/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:21:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 11:18:18 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			change_dir(char **env, char **path, char *buff, char *pwd)
{
	char		*value;

	if (chdir(*path) == 0)
	{
		value = ft_strjoin("=", pwd);
		setenv_var("OLDPWD", env, value);
		ft_strdel(&value);
		ft_strdel(&pwd);
		if (!(pwd = getcwd(buff, BUFF_SIZE)))
			pwd = ft_strdup("?");
		value = ft_strjoin("=", pwd);
		env = setenv_var("PWD", env, value);
		ft_strdel(&value);
	}
	else if (chdir(*path) == -1)
		return (cd_error(path, pwd));
	ft_strdel(&buff);
	ft_strdel(&pwd);
	return (1);
}

int			cd_builtin(char **path, char ***env)
{
	char		*buff[BUFF_SIZE];
	char		*pwd;

	pwd = NULL;
	*buff = NULL;
	if (path[0] && path[1])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (-1);
	}
	if (*path == NULL)
	{
		ft_strdel(path);
		*path = ft_strdup(get_env("$HOME", *env));
	}
	else if (!ft_strcmp(*path, "-"))
	{
		ft_strdel(path);
		*path = ft_strdup(get_env("$OLDPWD", *env));
	}
	*path ? *path = manage_tilde(path, *env) : 0;
	*path ? *path = manage_dollar(*path, *env) : 0;
	pwd = getcwd(*buff, BUFF_SIZE);
	!pwd ? pwd = ft_strdup(get_env("$PWD", *env)) : 0;
	return (change_dir(*env, path, *buff, pwd));
}

int			unsetenv_builtin(char **cmd, char ***env)
{
	char	*var;
	int		i;
	int		j;
	int		pos;

	if (!cmd[0] || cmd[1])
		return (error(2));
	i = -1;
	while (cmd && cmd[++i])
	{
		j = -1;
		j = strlen_to(cmd[i], '=');
		if (j == (int)ft_strlen(cmd[i]))
			return (error(2));
		var = ft_strndup(cmd[i], j);
		pos = find_pos(var, *env);
		ft_strdel(&var);
		if (pos != ft_tablen(*env))
			*env = remove_var(pos, *env);
	}
	return (1);
}

int			setenv_builtin(char **cmd, char ***env)
{
	char	*var;
	char	*value;
	int		i;
	int		j;

	i = -1;
	if (!cmd[0] || cmd[1])
		return (error(1));
	if ((value = ft_strdup(ft_strchr(*cmd, '='))))
		value = strdupfree(parse_value(value, *env));
	while (cmd && cmd[++i])
	{
		j = -1;
		j = strlen_to(cmd[i], '=');
		if (j == (int)ft_strlen(cmd[i]))
			return (error(1));
		if (!ft_strncmp(cmd[i], "$", 1))
			var = ft_strndup(&cmd[i][1], j - 1);
		else
			var = ft_strndup(cmd[i], j);
	}
	*env = setenv_var(var, *env, value);
	ft_strdel(&value);
	free(var);
	return (1);
}

int			echo_builtin(char **cmd, char ***env)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (!cmd[0] || (!ft_strcmp(*cmd, "-n") && !cmd[1]))
		return (1);
	else if (!ft_strcmp(*cmd, "-n"))
		flag = 1;
	i = -1;
	flag ? i++ : 0;
	while (cmd && cmd[++i])
	{
		cmd[i] = parse_value(cmd[i], *env);
		cmd[i] = manage_tilde(&cmd[i], *env);
		j = -1;
		while (cmd[i] && cmd[i][++j])
			if (cmd[i][j] != '"')
				write(1, &cmd[i][j], 1);
		cmd[i + 1] ? ft_putchar(' ') : 0;
	}
	!flag ? ft_putchar('\n') : 0;
	return (1);
}
