/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:17:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 16:50:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				split_cmd(char **cmds, char ***env)
{
	char		**cmd;
	int			ret;
	int			i;

	i = -1;
	ret = 0;
	while (cmds[++i])
	{
		cmds[i] = manage_dollar(cmds[i], *env);
		cmds[i] = manage_tilde(&cmds[i], *env);
		cmd = ft_split(cmds[i]);
		ft_strdel(&cmds[i]);
		if (*cmd)
			ret = execution(cmd, env);
		ft_tabfree(cmd);
		if (ret == -1)
			break ;
	}
	return (ret);
}

int				minishell(char ***env, char **cmd, char *input)
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
		if (split_cmd(cmd, env) == -1)
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
	struct passwd	*pw;
	uid_t			uid;

	uid = getuid();
	pw = getpwuid(uid);
	new_env = (char **)malloc(sizeof(new_env) * 9);
	new_env[0] = ft_strjoin("PWD=", getcwd(pwd, BUFF_SIZE));
	new_env[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	new_env[2] = ft_strjoin("HOME=", pw->pw_dir);
	new_env[3] = ft_strjoin("USER=", get_usr());
	new_env[4] = ft_strdup("TERM=xterm-256color");
	new_env[5] = ft_strdup("SHELL=minishell");
	new_env[6] = ft_strdup("SHLVL=0");
	new_env[7] = ft_strjoin("OLDPWD=", getcwd(pwd, BUFF_SIZE));
	new_env[8] = NULL;
	return (new_env);
}

char			**increase_shlvl(char **cmd, char **env)
{
	char		*shlvl;
	char		*lvl;
	char		**new_env;

	new_env = NULL;
	if (!ft_strcmp(cmd[0], "./minishell") || !ft_strcmp(cmd[0], "minishell"))
	{
		shlvl = get_value("$SHLVL", env);
		lvl = ft_itoa(ft_atoi(shlvl) + 1);
		shlvl = ft_strjoinclr("=", lvl, 2);
		new_env = setenv_var("SHLVL", env, shlvl);
		ft_strdel(&shlvl);
	}
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
		cmd = ft_tabcopy(cmd, av);
		if (!*env)
			new_env = mini_env(new_env, *av);
		else
			new_env = ft_tabcopy(new_env, env);
		new_env = setenv_var("SHELL", new_env, "=minishell");
		new_env = increase_shlvl(cmd, new_env);
		write(2, "\33[H\33[2J\33]0;", 7);
		minishell(&new_env, cmd, input);
		ft_tabfree(new_env);
	}
	else
		ft_putendl("Just run ./minishell without arguments");
	return (0);
}
