/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:22:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/18 17:37:35 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			walking_env(char *str, char **env, int j, int len)
{
	int		new_len;

	new_len = -1;
	while (env[++new_len])
	{
		if (ft_strncmp(str, env[new_len], j) == 0)
		{
			ft_strdel(&env[new_len]);
			return (new_len);
		}
	}
	return (len);
}

int		error(int num)
{
	if (num == 1)
	{
		ft_putendl("usage : setenv [ VAR=VALUE ]");
		return (-1);
	}
	if (num == 2)
	{
		ft_putendl("usage : unsetenv [ VAR=VALUE ]");
		return (-1);
	}
	return (0);
}

void	process_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, process_signal_handler);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		display_prompt();
		signal(SIGINT, signal_handler);
	}
}
