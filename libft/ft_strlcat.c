/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:13:12 by fcatusse          #+#    #+#             */
/*   Updated: 2019/01/30 18:13:22 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	if (size < dest_len)
		return (size + ft_strlen((char*)src));
	while (src[i] && dest_len < size - 1)
		dest[dest_len++] = src[i++];
	dest[dest_len] = '\0';
	return (ft_strlen((char*)src) + dest_len - i);
}
