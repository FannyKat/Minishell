/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:29:02 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/22 18:32:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabcopy(char **tab_dest, char **tab)
{
	int		i;

	i = -1;
	if (!(tab_dest = malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (tab && tab[++i])
		if (!(tab_dest[i] = ft_strdup(tab[i])))
		{
			ft_tabfree(tab_dest);
			return (NULL);
		}
	tab_dest[i] = 0;
	return (tab_dest);
}
