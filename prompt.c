/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:27:57 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/10 16:06:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_usr(void)
{
	struct passwd	*pwd;
	uid_t			uid;

	uid = getuid();
	pwd = getpwuid(uid);
	return (pwd->pw_name);
}

void			display_prompt(void)
{
	char		path[BUFF_SIZE];
	char		*prompt;
	int			len;

	len = -1;
	if (getcwd(path, BUFF_SIZE))
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
