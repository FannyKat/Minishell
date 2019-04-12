/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:19:11 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/10 11:46:23 by fcatusse         ###   ########.fr       */
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

# define BUFF_SIZE 100

void	display_prompt(void);
void	signal_handler(int signum);
void	process_signal_handler(int signum);
char	*get_usr(void);
int		execution(char **cmd, char ***env);
int		echo_builtin(char **cmd, char ***env);
int		setenv_builtin(char **cmd, char ***env);
int		unsetenv_builtin(char **cmd, char ***env);
int		cd_builtin(char **path, char ***env);
int		error(int num);
int		cd_error(char **path, char *pwd);
int		exit_shell(char *input);
int		find_pos(char *var, char **env);
char	**realloc_env(char **env, int len);
char	**remove_var(int pos, char **env);
char	**setenv_var(char *var, char **env, char *value);
char	*get_value(char *var, char **env);
char	*manage_tilde(char **path, char **env);
char	*manage_dollar(char *path, char **env);
char	*parse_value(char *value, char **env);

#endif
