/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:46:25 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/21 18:46:30 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**realloc_env(int len, char **env)
{
	int		i;
	char	**new;

	/** MALLOC ERROR ALLOC +1**/
	i = -1;
	new = (char **)malloc(sizeof(char *) * (len + 1));	
	while (env && env[++i])
	{
		new[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	while (i < len + 1)
		new[i++] = NULL;	
	free(env);
	return (new);
}

int			find_pos(char *var, char **env)
{	
	int		i;
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

char			**setenv_var(char *var, char **env, char *value)
{
	int			i;
	int			len;
	char		*tmp;

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
		env = realloc_env(len, env);
		if (value)
			env[i] = ft_strjoin(var, tmp);
		else
			env[i] = ft_strjoin(var, "=");
	}
	ft_strdel(&tmp);
	return (env);
}

char			**remove_var(int pos, char **env)
{
	int			i;
	int			count;

	free(env[pos]);
	env[pos] = NULL;
	count = 0;
	i = pos;
	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1]);	
		free(env[i + 1]);
		i++;
		count++;
	}
	env[i] = 0;
	return (env);
}
