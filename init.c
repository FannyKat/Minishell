/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:17:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/08 15:03:23 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				split_cmd(char **cmds, char ***env)
{
	char		**cmd;
	int			i;
	int			ret;

	i = -1;
	ret = 0;
	while (cmds[++i])
	{
		cmds[i] = manage_dollar(cmds[i], *env);
		cmds[i] = manage_tilde(&cmds[i], *env);
		cmd = ft_split(cmds[i]);
		if (*cmd)
			ret = exec_cmd(cmd, env);
		ft_tabfree(cmd);
		if (ret == -1)
			break ;
	}
	return (ret);
}

char			*manage_dollar(char *cmd, char **env)
{
	char		*value;
	char		*tmp;
	int			i;

	i = -1;
	value = NULL;
	if (cmd && isstart(cmd, "$"))
	{
		if ((tmp = ft_strchr(cmd, '/')))
		{
			tmp = ft_strdup(tmp);
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

int				minishell(char ***new_env, char **cmd, char *input)
{
	while (1)
	{
		display_prompt();
		signal(SIGINT, signal_handler);
		if (get_next_line(0, &input) < 1)
			return (0);
		if (exit_shell(input))
		{
			ft_strdel(&input);
			ft_tabfree(cmd);
			return (0);
		}
		ft_tabfree(cmd);
		cmd = ft_strsplit(input, ';');
		ft_strdel(&input);
		if (split_cmd(cmd, new_env) == -1)
		{
			ft_tabfree(cmd);
			break ;
		}
	}
	ft_tabfree(cmd);
	return (0);
}

char			**mini_env(char **new_env, char *pwd)
{
	new_env = (char **)malloc(sizeof(new_env) * 9);
	new_env[0] = ft_strjoin("PWD=", getcwd(pwd, BUFF_SIZE));
	new_env[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	new_env[2] = ft_strjoin("HOME=", get_home());
	new_env[3] = ft_strjoin("USER=", get_usr());
	new_env[4] = ft_strdup("TERM=xterm-256color");
	new_env[5] = ft_strjoin("SHELL=", get_shell());
	new_env[6] = ft_strdup("SHLVL=1");
	new_env[7] = ft_strjoin("OLDPWD=", get_home());
	new_env[8] = NULL;
	return (new_env);
}

int				main(int ac, char **av, char **env)
{
	char		**new_env;
	char		**cmd;
	char		*input;

	cmd = NULL;
	new_env = NULL;
	input = NULL;
	if (!isatty(0))
		return (0);
	if (ac == 1 && !av[1])
	{
		if (!*env)
			new_env = mini_env(new_env, *av);
		else
			new_env = ft_tabcopy(new_env, env);
		minishell(&new_env, cmd, input);
		ft_tabfree(new_env);
	}
	else
		ft_putendl("Just run ./minishell without arguments");
	return (0);
}
