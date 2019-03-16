#include "minishell.h"

void		display_prompt()
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

int			main(int ac, char **av, char **env)
{
	char		**cmds;
	char		*input;

	if (ac == 1)
	{
		while (1)
		{
			display_prompt();
			signal(SIGINT, signal_handler);
			get_next_line(0, &input);
			if (input && !ft_strcmp(input, "exit"))
				return (0);
			cmds = ft_split(input);
			if (*cmds)
				exec_cmd(cmds, env);
		}
	}
	return (1);
}
