/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:22:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/08 14:30:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					cd_error(char **path, char *pwd)
{
	struct stat		buf;

	lstat(*path, &buf);
	if (access(*path, F_OK) == -1)
		my_printf("cd: %s: No such file or directory\n", *path);
	else if (!(buf.st_mode & S_IFDIR))
		my_printf("cd: %s: Not a directory\n", *path);
	else if (access(*path, R_OK) == -1 || access(*path, X_OK) == -1
			|| access(*path, W_OK) == -1)
		my_printf("cd: %s: Permission Denied\n", *path);
	ft_strdel(&pwd);
	return (-1);
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
	return (0);
}

int					exit_shell(char *input)
{
	int				i;

	i = -1;
	while (input && input[++i] && ft_isspace(input[i]))
		;
	if (input && !ft_strncmp(input + i, "exit", 4))
		return (!ft_isalnum(input[i + 4]));
	return (0);
}

void				signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, signal_handler);
		ft_putstr("\n");
		display_prompt();
	}
}

void				process_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, process_signal_handler);
		ft_putstr("\n");
	}
}
