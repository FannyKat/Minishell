/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:17:34 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/07 11:10:05 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*srce;

	dest = (char *)dst;
	srce = (char *)src;
	if (dest > srce)
	{
		while (len--)
			dest[len] = srce[len];
	}
	else
		ft_memcpy(dest, srce, len);
	return (dest);
}
