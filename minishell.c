#include "minishell.h"
#include <stdio.h>

void		print_prompt()
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

/*void		builtins(char **av, char **env)
{
	int		i;

	i = 0;
	if (!ft_strcmp(*av, "ls"))
		execve(*av, "ls", NULL);
	if (!ft_strncmp(*av, "echo", 3))
		execve("/bin/echo", av, NULL);
	if (!ft_strcmp(*av, "env"))
	{
		while (*env)
			my_printf("%s\n", env[i++]);
	}
	if (!ft_strcmp(*av, "exit"))
		exit(0);
}*/

int					the_fork(char **path, char **env, char **builtin)
{
	struct stat		fd;
	pid_t			father;

		printf("%s %s %s\n", builtin[0], *builtin, *env);
	if (builtin && !lstat(builtin[0], &fd))
	{
		father = fork();
		if (father == 0)
		{
			execve(builtin[0], builtin, env);
			//builtins(builtin, env);
		}
		else if (father > 0)
		{
			wait(NULL);
		}
		return (1);
	}
	return (0);
}

char		**walking_path(char **env, char *str)
{
	char	**tab;
	int		i;
	int		len;

	i = 0;
	while (env[i++])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		if (!ft_strncmp(str, env[i], len))
		{
			tab = ft_strsplit(env[i] + len + 1, ':');
			break ;
		}
	}
	return (tab);
}

void		find_builtin(char **builtin, char **env)
{
	char	**abs_path;
	char	*path;
	int		i;

	i = 0;
	abs_path = walking_path(env, "PATH");
	while (abs_path && abs_path[i++])
	{
		path = ft_strcat(*abs_path, "/");
		path = ft_strcat(*abs_path, builtin[0]);
		printf("[%s]\n", path);
		the_fork(&path, env, builtin);
	}
}

int			main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		while (1)
		{
			print_prompt();
			get_next_line(0, av);
			if (*av && !ft_strcmp(*av, "exit"))
				return (0);
			av = ft_split(*av);
			if (*av)
				find_builtin(av, env);
		}
	}
	return (1);
}
