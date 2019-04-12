/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:45:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 10:40:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**realloc_tab(char **array, int len)
{
	char		**new;
	int			i;
	int			j;

	i = -1;
	j = -1;
	if (!(new = (char **)malloc(sizeof(*new) * (len + 1))))
		return (array);
	while (array && array[++i])
	{
		if (!(new[++j] = ft_strdup(array[i])))
		{
			ft_tabfree(new);
			return (array);
		}
	}
	while (j++ < len)
		new[j] = NULL;
	ft_tabfree(array);
	return (new);
}
