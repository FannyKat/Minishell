/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:02:09 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/08 10:37:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char *dest;
	unsigned char *src;

	dest = (unsigned char *)s1;
	src = (unsigned char *)s2;
	while (n--)
	{
		*dest++ = *src;
		if (*src++ == (unsigned char)c)
			return (dest);
	}
	return (NULL);
}
