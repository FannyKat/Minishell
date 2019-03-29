/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:45:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 13:50:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**realloc_tab(char **tab, int len)
{
	int		i;
	int		j;
	char		**new;

	i = -1;
	j = -1;
	if(!(new = (char **)malloc(sizeof(*new) * (len + 1))))
		return (tab);
	while (tab && tab[++i])
	{
		if(!(new[++j] = ft_strdup(tab[i])))
		{
			ft_tabfree(new);
			return (tab);
		}
	}
	while (j++ < len + 1)
		new[j] = NULL;
	ft_tabfree(tab);
	return (new);
}
