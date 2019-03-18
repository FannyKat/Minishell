/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:21:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/18 17:38:08 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unsetenv_builtin(char **av, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (av && av[++i])
	{
		j = -1;
		while (av[i][++j] != '=')
			;
		if (av[i][j] == '=')
		{
			while (av[i][j++] != '=')
				;
			if (av[i][j + 1] == '=' || av[i + 1])
				return (error(2));
		}
	}
	i = -1;
	while (env[++i])
		if (!ft_strcmp(env[i], av[0]))
			ft_strdel(&env[i]);
	return (1);
}

int			setenv_builtin(char **av, char **env)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	len = -1;
	while (env[++len])
		;
	while (av && av[++i])
	{
		j = -1;
		while (av[i][++j] != '=')
			str = ft_strdup(av[i]);
		len = walking_env(str, env, j, len);
		if (av[i][j] == '=')
		{
			while (av[i][j++] != '=')
				str = ft_strcat(str, av[i]);
			if (av[i][j + 1] == '=' || av[i + 1])
				return (error(1));
		}
	}
	env[len] = ft_strdup(str);
	env[++len] = 0;
	return (1);
}

int			echo_builtin(char **av)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (!av[0])
		return (1);
	else if (av[0][0] == '-' && av[0][1] == 'n')
		flag = 1;
	i = -1;
	flag ? i++ : 0;
	while (av && av[++i])
	{
		j = -1;
		while (av[i] && av[i][++j])
		{
			if (!(av[i][j] == '"'))
				write(1, &av[i][j], 1);
		}
		if (av[i + 1])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
	return (1);
}
