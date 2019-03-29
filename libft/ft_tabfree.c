/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:26:20 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 18:20:46 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabfree(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab && tab[++i])
		ft_strdel(&tab[i]);
	free(tab);
}
