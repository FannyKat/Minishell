#include "minishell.h"

char			*get_name(void)
{
	struct passwd	*pwd;
	uid_t		uid;

	uid = getuid();
	pwd = getpwuid(uid);
	return (pwd->pw_name);
}

void			display_prompt(void)
{
	char		path[BUFF_SIZE];
	char		*prompt;
	int			len;

	getcwd(path, BUFF_SIZE);
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
	if (!prompt)
		prompt = ft_strdup("?");
	my_printf("\033[38;5;177m[%s]\033[0m ", prompt);
	ft_strdel(&prompt);
}
