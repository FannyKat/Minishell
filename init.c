/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:17:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/18 18:23:45 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_prompt(void)
{
	char	path[100];
	char	*prompt;
	int		len;

	getcwd(path, 100);
	len = ft_strlen(path) - 1;
	prompt = NULL;
	while (path[len--])
	{
		if (path[len] == '/')
		{
			prompt = ft_strdup(path + len + 1);
			break ;
		}
	}
	my_printf("\033[38;5;177m[%s]\033[0m ", prompt);
}

int			exit_shell(char *input)
{
	int		i;

	i = -1;
	while (input && input[++i] && ft_isspace(input[i]))
		;
	if (input && !ft_strncmp(input + i, "exit", 4))
	{
		return (!ft_isalnum(input[i + 4]));
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	char	**cmd;
	char	*input;
	int		ret;

	if (!isatty(0))
		return (0);
	if (ac == 1 && !av[1])
	{
		while (1)
		{
			display_prompt();
			signal(SIGINT, signal_handler);
			if (get_next_line(0, &input) <= 0)
				return (0);
			if (exit_shell(input))
				return (0);
			cmd = ft_strsplit(input, ' ');
			if (*cmd)
				if ((ret = exec_cmd(cmd, env)) == -1)
				{
					ft_strdel(&input);
					break ;
				}
			ft_strdel(&input);
		}
	}
	ft_putendl("Just run ./minishell without arguments");
	return (0);
}
