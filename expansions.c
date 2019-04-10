/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:17:37 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/10 19:47:30 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*parse_value(char *value, char **env)
{
	int			i;
	int			j;
	int			pos;
	char		*tmp;

	i = -1;
	tmp = NULL;
	while (value[++i])
	{
		if (value[i] == '$')
		{
			j = 0;
			i++;
			pos = i;
			while (ft_isupper(value[i++]))
				j++;
			tmp = ft_strsub(value, i - j - 2, j + 2);
			printf("%s\n", tmp);
			tmp = manage_dollar(tmp, env);
		}
	}
	value = ft_strjoin("=", tmp);
	return (value);
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
