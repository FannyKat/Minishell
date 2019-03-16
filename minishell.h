#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>

void	signal_handler(int signum);
void	process_signal_handler(int signum);
void	display_prompt();
int	exec_cmd(char **cmd, char **env);

#endif
