/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:17:56 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/10 19:34:05 by fcatusse         ###   ########.fr       */
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
	new_env[5] = ft_strjoin("SHELL=", pw->pw_shell);
	new_env[6] = ft_strdup("SHLVL=2");
	new_env[7] = ft_strjoin("OLDPWD=", pw->pw_dir);
	new_env[8] = NULL;
	return (new_env);
}

void			increase_shlvl(char **cmd, char ***env)
{
	char		*shlvl;
	char		*lvl;

	if (!ft_strcmp(cmd[0], "./minishell"))
	{
		shlvl = get_value("$SHLVL", *env);
		lvl = ft_itoa(ft_atoi(shlvl) + 1);
		shlvl = ft_strjoin("=", lvl);
		setenv_var("SHLVL", *env, shlvl);
		ft_strdel(&shlvl);
		ft_strdel(&lvl);
	}
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
		increase_shlvl(av, &new_env);
		minishell(&new_env, cmd, input);
		ft_tabfree(new_env);
	}
	else
		ft_putendl("Just run ./minishell without arguments");
	return (0);
}
