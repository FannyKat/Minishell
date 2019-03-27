/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:46:25 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 17:25:20 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*manage_opt(char **path, char ***env)
{
	if (*path && !ft_strncmp(*path, "$", 1))
	{
		path[0] = get_value(*path, *env);
		path[1] = NULL;
	}
	else if (*path == NULL || !ft_strcmp(*path, "~"))
	{
		path[0] = ft_strdup(get_value("$HOME", *env));
		path[1] = NULL;
	}
	else if (!ft_strcmp(*path, "-"))
	{
		path[0] = ft_strdup(get_value("$OLDPWD", *env));
		path[1] = NULL;
	}
	return (*path);	
}

int		find_pos(char *var, char **env)
{
	int	i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(var, "=");
	while (env[++i])
	{
		if (ft_strstart(env[i], tmp))
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
	int	pos;
	
	pos = find_pos(var + 1, env);
	value = NULL;
	if (env[pos])
	{
		value = ft_strchr(env[pos], '=');
		value++;
	}
	return (value);
}

char		**setenv_var(char *var, char **env, char *value)
{
	int	i;
	int	len;
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
		env = realloc_tab(env, len);
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
	int	i;
	int	count;

	free(env[pos]);
	env[pos] = NULL;
	i = pos;
	count = pos + 1;
	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1]);	
		free(env[i + 1]);
		i++;
		count++;
	}
	env = realloc_tab(env, count - 1);
	return (env);
}
