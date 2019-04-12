/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdupfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:28:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 09:29:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*strdupfree(char *s1)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	ft_strdel(&s1);
	dest[i] = '\0';
	return (dest);
}
