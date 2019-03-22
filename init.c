/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:17:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/22 19:05:02 by fcatusse         ###   ########.fr       */
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
		if (path[len + 1] == '/')
		{
			prompt = ft_strdup("/");
			break ;
		}
		if (path[len] == '/')
		{
			prompt = ft_strdup(path + len + 1);
			break ;
		}
	}
	my_printf("\033[38;5;177m[%s]\033[0m ", prompt);
	free(prompt);
}

int			minishell(char ***new_env)
{
	char	*input;
	char	**cmd;

	while (1)
	{
		display_prompt();
		signal(SIGINT, signal_handler);
		if (get_next_line(0, &input) <= 0)
			return (0);
		if (exit_shell(input))
		{
			ft_strdel(&input);
			return (0);
		}
		cmd = ft_split(input);
		ft_strdel(&input);
		if (*cmd)
			if (exec_cmd(cmd, new_env) == -1)
			{
				ft_tabfree(cmd);
				break ;
			}
	}
	ft_tabfree(cmd);
	return (0);
}

char		**mini_env(char **new_env, char *pwd)
{
	/** TO DO HOME= **/
	new_env = (char **)malloc(sizeof(new_env) * 5);	
	new_env[0] = ft_strjoin("PWD=", getcwd(pwd, BUFF_SIZE));
	new_env[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	new_env[2] = ft_strdup("TERM=xterm-256color");
	new_env[3] = ft_strdup("OLDPWD=/Users/fcatusse");
	new_env[4] = NULL;
	return (new_env);
}

int			main(int ac, char **av, char **env)
{
	char	**new_env;

	new_env = NULL;
	if (!isatty(0))
		return (0);
	if (ac == 1 && !av[1])
	{
		if (!*env)
			new_env = mini_env(new_env, *av);
		else
			new_env = ft_tabcopy(new_env, env);
		minishell(&new_env);
		ft_tabfree(new_env);
	}
	else
		ft_putendl("Just run ./minishell without arguments");
	return (0);
}
