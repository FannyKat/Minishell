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
	char	**new;

	i = -1;
	new = (char **)malloc(sizeof(*new) * (len + 1));
	while (tab && tab[++i] && i < len)
		new[i] = ft_strdup(tab[i]);
	ft_tabfree(tab);
	return (new);
}
