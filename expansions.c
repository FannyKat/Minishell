/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:17:37 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/11 20:26:12 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*check_var(char *value, char *cmd, char **env, int i)
{
	char		*tmp;
	char		*var;
	char		*new;
	int			j;
	int			pos;

	new = NULL;
	tmp = NULL;
	var = NULL;
	j = 0;
	pos = i;
	while (ft_isupper(cmd[++i]))
		j++;
	tmp = ft_strndup(&cmd[pos], j + 1);
	var = manage_dollar(tmp, env);
	value ? new = ft_strjoin(value, var) : 0;
	!value ? new = ft_strdup(var) : 0;
	return (new);
}

char			*parse_value(char *cmd, char **env)
{
	char		*new_value;
	int			i;

	i = -1;
	new_value = NULL;
	while (cmd[++i])
	{
		if (cmd[i] == '$')
		{
			new_value = check_var(new_value, cmd, env, i);
			while (ft_isupper(cmd[++i]))
				;
			i--;
		}
		else
		{
			if (new_value)
				new_value = ft_strnjoin(new_value, &cmd[i], 1);
			else
				new_value = ft_strndup(&cmd[i], 1);
		}
	}
	return (new_value);
}

char			*manage_dollar(char *cmd, char **env)
{
	char		*value;
	char		*tmp;
	int			i;

	i = -1;
	tmp = NULL;
	if (cmd && isstart(cmd, "$"))
	{
		if ((tmp = ft_strchr(cmd, '/')))
		{
			tmp = ft_strdup(ft_strchr(cmd, '/'));
			i = strlen_to(cmd, '/');
			value = ft_strndup(cmd, i);
			ft_strdel(&cmd);
			cmd = ft_strjoin(get_value(value, env), tmp);
			ft_strdel(&value);
			ft_strdel(&tmp);
			return (cmd);
		}
		value = ft_strdup(cmd);
		ft_strdel(&cmd);
		cmd = ft_strdup(get_value(value, env));
		ft_strdel(&value);
	}
	return (cmd);
}

char			*manage_tilde(char **path, char **env)
{
	char		*value;

	value = NULL;
	if (path && isstart(*path, "~"))
	{
		if (!ft_strcmp(*path, "~") || !ft_strcmp(*path + 1, get_usr()))
		{
			ft_strdel(path);
			*path = ft_strdup(get_value("$HOME", env));
			return (*path);
		}
		if ((value = ft_strchr(*path, '/')))
		{
			value = ft_strdup(ft_strchr(*path, '/'));
			ft_strdel(path);
			*path = ft_strjoin(get_value("$HOME", env), value);
			ft_strdel(&value);
		}
	}
	return (*path);
}
