/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:51:19 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/15 13:54:51 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		c;
	int		size;
	char	tmp;

	c = 0;
	size = 0;
	if (!str)
		return (NULL);
	while (str[size])
		size++;
	size -= 1;
	while (c < size)
	{
		tmp = str[size];
		str[size] = str[c];
		str[c] = tmp;
		c++;
		size--;
	}
	return (str);
}
