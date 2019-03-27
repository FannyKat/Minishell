/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:21:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 17:25:09 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_builtin(char **path, char ***env)
{
	char		*buff[BUFF_SIZE + 1];
	char		*pwd;

	if (path[1])
		return (error(3));
	*path = manage_opt(path, env);
	pwd = getcwd(*buff, BUFF_SIZE);
	if (!pwd)
		pwd = ft_strdup("/home/fanny");
	if (chdir(*path) == 0)
	{
		setenv_var("OLDPWD", *env, ft_strjoin("=", pwd));
		ft_strdel(&pwd);
		pwd = getcwd(*buff, BUFF_SIZE);
		setenv_var("PWD", *env, ft_strjoin("=", pwd));
		ft_strdel(&pwd);
	}
	else if (chdir(*path) == -1)
	{
		if (access(*path, F_OK) == -1)
			my_printf("cd: %s: No such file or directory\n", *path);
		else if (access(*path, R_OK) == -1 || access(*path, X_OK) == -1)
			my_printf("cd: %s: Permission Denied\n", *path);
		else	
			my_printf("cd: %s: Not a directory\n", *path);
		return (-1);
	}
	return (1);
}

int			unsetenv_builtin(char **cmd, char ***env)
{
	char		*var;
	int		i;
	int		j;
	int		pos;

	if (!cmd[0] || cmd[1])
		return (error(1));
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
		if ((pos + 1) != ft_tablen(*env) && env[pos])
			*env = remove_var(pos, *env);
	}
	return (1);
}

int			setenv_builtin(char **cmd, char ***env)
{
	char		*var;
	char		*value;
	int		i;
	int		j;

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

int			echo_builtin(char **cmd, char ***env)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (!cmd[0])
		return (1);
	else if (cmd[0][0] == '-' && cmd[0][1] == 'n')
		flag = 1;
	else if (cmd[0][0] == '$')
		*cmd = get_value(*cmd, *env);
	i = -1;
	flag ? i++ : 0;
	while (cmd && cmd[++i])
	{
		j = -1;
		while (cmd[i] && cmd[i][++j])
			if (!(cmd[i][j] == '"'))
				write(1, &cmd[i][j], 1);
		if (cmd[i + 1])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
	return (1);
}
