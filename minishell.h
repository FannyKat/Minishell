/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:19:11 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/21 18:41:29 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include <pwd.h>

void	signal_handler(int signum);
void	process_signal_handler(int signum);
void	display_prompt(void);
int		exec_cmd(char **cmd, char ***env);
int		echo_builtin(char **av);
int		setenv_builtin(char **av, char ***env);
int		unsetenv_builtin(char **av, char ***env);
int		cd_builtin(char **path, char ***env);
int		error(int num);
int		walking_env(char *str, char **env, int j, int len);
int		find_pos(char *var, char **env);
char	**realloc_env(int len, char **env);
char	**remove_var(int pos, char **env);
char	**setenv_var(char *var, char **env, char *value);

#endif
