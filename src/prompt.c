/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:27:57 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 09:30:41 by fcatusse         ###   ########.fr       */
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

	prompt = NULL;
	if (!getcwd(path, BUFF_SIZE))
	{
		prompt = ft_strdup("?");
		my_printf("\033[38;5;177m[%s]\033[0m ", prompt);
	}
	else
	{
		prompt = ft_strdup(ft_strrchr(path, '/'));
		my_printf("\033[38;5;177m[%s]\033[0m ", prompt + 1);
	}
	ft_strdel(&prompt);
}
