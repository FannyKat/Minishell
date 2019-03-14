/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:47:39 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/15 13:52:46 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int i;
	int *tab;
	int diff;

	if (min >= max)
		return (0);
	i = 0;
	diff = max - min;
	tab = (int *)malloc(sizeof(int) * (diff));
	while (min < max)
	{
		tab[i] = min;
		i++;
		min++;
	}
	return (tab);
}
