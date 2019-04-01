/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:22:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/01 14:31:54 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*get_name(void)
{
	struct passwd	*pwd;
	uid_t			uid;

	uid = getuid();
	pwd = getpwuid(uid);
	return (pwd->pw_name);
}

int					error(int num)
{
	if (num == 1)
	{
		ft_putendl_fd("usage : setenv [ VAR=VALUE ]", 2);
		return (-1);
	}
	if (num == 2)
	{
		ft_putendl_fd("usage : unsetenv [ VAR=VALUE ]", 2);
		return (-1);
	}
	if (num == 3)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (-1);
	}
	return (0);
}

int				exit_shell(char *input)
{
	int			i;

	i = -1;
	while (input && input[++i] && ft_isspace(input[i]))
		;
	if (input && !ft_strncmp(input + i, "exit", 4))
		return (!ft_isalnum(input[i + 4]));
	return (0);
}

void			process_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, process_signal_handler);
	}
}

void			signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		display_prompt();
		signal(SIGINT, signal_handler);
	}
}
