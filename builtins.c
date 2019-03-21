/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:21:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/21 18:54:17 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_builtin(char **path, char ***env)
{
	char	*pwd;
	//char	*old_pwd;
	char	*new_path;
	//char	old_path[100];

	//getcwd(old_path, 100);
	pwd = "PWD=";
	//old_pwd = ft_strjoin("OLDPWD=", old_path);
	if (chdir(*path) == -1)
	{
		my_printf("cd: not a directory: %s\n", *path);
		return (-1);
	}
	else
	{
		/** GET OLDPWD **/
		new_path = ft_strnew(42);
		new_path = getcwd(*path, 2048);
		*path = ft_strjoin(pwd, new_path);
		setenv_builtin(path, env);
	//	setenv_builtin(&old_pwd, env);
		free(new_path);
	}
	return (1);
}

int				unsetenv_builtin(char **cmd, char ***env)
{
	char		*var;
	int			i;
	int			j;
	int			pos;

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
		if (env[pos])
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
	return (1);
}

int			echo_builtin(char **av)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (!av[0])
		return (1);
	else if (av[0][0] == '-' && av[0][1] == 'n')
		flag = 1;
	i = -1;
	flag ? i++ : 0;
	while (av && av[++i])
	{
		j = -1;
		while (av[i] && av[i][++j])
		{
			if (!(av[i][j] == '"'))
				write(1, &av[i][j], 1);
		}
		if (av[i + 1])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
	return (1);
}
