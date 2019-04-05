/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:46:25 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/03 18:06:48 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*manage_opt(char **path, char ***env)
{
	char	*value;

	value = NULL;
	if (*path && !ft_strncmp(*path, "$", 1))
	{
		value = ft_strdup(*path);
		ft_strdel(path);
		*path = ft_strdup(get_value(value, *env));
		ft_strdel(&value);
	}
	else if (isstart(*path, "~"))
	{
		if (!ft_strcmp(*path, "~"))
		{
			ft_strdel(path);
			*path = ft_strdup(get_value("$HOME", *env));
			return (*path);
		}		
		value = ft_strdup(ft_strchr(*path, '/'));
		ft_strdel(path);
		*path = ft_strjoin(get_value("$HOME", *env), value);
		ft_strdel(&value);
	}
	return (*path);
}

int			find_pos(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(var, "=");
	while (env[++i])
	{
		if (isstart(env[i], tmp))
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (i);
}

char		*get_value(char *var, char **env)
{
	char	*value;
	int		pos;

	pos = find_pos(var + 1, env);
	value = NULL;
	if (env[pos])
	{
		value = ft_strchr(env[pos], '=');
		value++;
	}
	if (!value)
		value = "";
	return (value);
}

char		**setenv_var(char *var, char **env, char *value)
{
	int		i;
	int		len;
	char	*tmp;

	i = find_pos(var, env);
	len = ft_tablen(env);
	tmp = ft_strdup(value);
	if (env[i])
	{
		ft_strdel(&env[i]);
		if (value)
			env[i] = ft_strjoin(var, tmp);
		else
			env[i] = ft_strjoin(var, "=");
	}
	else
	{
		env = realloc_tab(env, len + 1);
		if (value)
			env[i] = ft_strjoin(var, tmp);
		else
			env[i] = ft_strjoin(var, "=");
	}
	ft_strdel(&tmp);
	return (env);
}

char		**remove_var(int pos, char **env)
{
	int		i;

	free(env[pos]);
	i = pos;
	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1]);
		free(env[i + 1]);
		i++;
	}
	env[i] = NULL;
	env = realloc_tab(env, i);
	return (env);
}
