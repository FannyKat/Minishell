/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:46:25 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 10:02:20 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_pos(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!ft_strncmp(var, "$", 1))
		var++;
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

char		*get_env(char *var, char **env)
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
