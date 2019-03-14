#include "minishell.h"
#include <stdio.h>

void		print_prompt()
{
	char	path[100];
	char	*prompt;
	int		len;

	getcwd(path, 100);
	len = ft_strlen(path) - 1;
	while (path[len--])
	{
		if (path[len] == '/')
		{		
			prompt = ft_strdup(path + len + 1);
			break ;
		}
	}
	ft_putstr("[minishell] ");
}

void		builtins(char **av, char **env)
{
	int		i;

	i = 0;
	if (!ft_strcmp(*av, "ls"))
		execve("/bin/ls", av, NULL);
	if (!ft_strncmp(*av, "echo", 3))
		execve("/bin/echo", av, NULL);
	if (!ft_strcmp(*av, "env"))
	{
		while (*env)
			printf("%s\n", env[i++]);
	}
	if (!ft_strcmp(*av, "exit"))
		exit(0);
}

int			the_fork(char **av, char **env)
{
	struct stat		fd;
	pid_t			father;

	if (!lstat(*av, &fd))
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
		}
		else if (father == 0)
		{
			builtins(av, env);
		}
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		while (1)
		{
			print_prompt();
			get_next_line(0, av);
			if (!ft_strcmp(*av, "exit"))
				return (0);
			the_fork(av, env);
		}
	}
}
