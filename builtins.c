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

void			get_path(char **path, char ***env, int num)
{
	char		*pwd;
	char		*old_pwd;
	char		**old_path;

	if (num == 1)
	{
		old_path = malloc(sizeof(char *) * BUFF_SIZE);
		*old_path = NULL;
		old_pwd = ft_strjoin("OLDPWD=", getcwd(*old_path, BUFF_SIZE));
		*old_path = ft_strdup(old_pwd);
		setenv_builtin(old_path, env);
		free(old_pwd);
		free(*old_path);
	}
	if (num == 2)
	{
		pwd = ft_strjoin("PWD=", getcwd(*path, BUFF_SIZE));		
		*path = ft_strdup(pwd);
		setenv_builtin(path, env);
		free(pwd);
		free(*path);
	}
}

int				cd_builtin(char **path, char ***env)
{
	struct stat	fd;

	*path = manage_opt(path, env);
	get_path(path, env, 1);
	if (chdir(*path) == -1)
	{
		lstat(*path, &fd);
		if (fd.st_mode & S_IRUSR || fd.st_mode & S_IWUSR
			|| fd.st_mode & S_IRGRP || fd.st_mode & S_IWGRP
			|| fd.st_mode & S_IROTH || fd.st_mode & S_IWOTH)
			my_printf("cd: %s: Permission Denied\n", *path);
		else
			my_printf("cd: Not a directory: %s\n", *path);
	//	ft_tabfree(path);
		return (-1);
	}
	else
		get_path(path, env, 2);
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
	free(var);
	return (1);
}

int				echo_builtin(char **cmd, char ***env)
{
	int			i;
	int			j;
	int			flag;

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
