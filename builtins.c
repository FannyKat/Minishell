/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:21:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/04 12:46:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				change_dir(char **env, char **path, char *buff, char *pwd)
{
	char		*value;

	if (chdir(*path) == 0)
	{
		value = ft_strjoin("=", pwd);
		setenv_var("OLDPWD", env, value);
		ft_strdel(&value);
		ft_strdel(&pwd);
		if (!(pwd = getcwd(buff, BUFF_SIZE)))
			pwd = ft_strjoin("/home/", get_name());
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

int				cd_builtin(char **path, char ***env)
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
		*path = ft_strdup(get_value("$HOME", *env));	
	}
	else if (!ft_strcmp(*path, "-"))
	{
		ft_strdel(path);
		*path = ft_strdup(get_value("$OLDPWD", *env));	
	}
	*path ? *path = manage_opt(path, env) : 0;
	pwd = getcwd(*buff, BUFF_SIZE);
	!pwd ? pwd = ft_strjoin("/home/", get_name()) : 0;
	return (change_dir(*env, path, *buff, pwd));
}

int				unsetenv_builtin(char **cmd, char ***env)
{
	char		*var;
	int			i;
	int			j;
	int			pos;

	if (!cmd[0] || cmd[1])
		return (error(2));
	i = -1;
	while (cmd && cmd[++i])
	{
		j = -1;
		while (cmd[i][++j] && cmd[i][j] != '=')
			;
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

int				setenv_builtin(char **cmd, char ***env)
{
	char		*var;
	char		*value;
	int			i;
	int			j;

	i = -1;
	if (!cmd[0] || cmd[1])
		return (error(1));
	value = ft_strchr(*cmd, '=');
	while (cmd && cmd[++i])
	{
		j = -1;
		while (cmd[i][++j] && cmd[i][j] != '=')
			;
		if (j == (int)ft_strlen(cmd[i]))
			return (error(1));
		var = ft_strndup(cmd[i], j);
	}
	*env = setenv_var(var, *env, value);
	free(var);
	return (1);
}

int				echo_builtin(char **cmd, char ***env)
{
	int			i;
	int			j;
	int			flag;

	flag = 0;
	if (!cmd[0] || (!ft_strcmp(*cmd, "-n") && !cmd[1]))
		return (1);
	else if (cmd[0][0] == '-' && cmd[0][1] == 'n' && !cmd[0][2])
		flag = 1;
	!flag ? *cmd = manage_opt(cmd, env) : 0;
	flag ? cmd += 1 : 0;
	flag ? *cmd = manage_opt(cmd, env) : 0;
	i = -1;
	while (cmd && cmd[++i])
	{	
		j = -1;
		while (cmd[i] && cmd[i][++j])
			if (!(cmd[i][j] == '"'))
				write(1, &cmd[i][j], 1);
		if (cmd[i + 1])
			ft_putchar(' ');
	}
	!flag ? ft_putchar('\n') : 0;	
	return (1);
}
