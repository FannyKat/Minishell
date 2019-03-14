/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:13:26 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/14 15:56:27 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s2[j] && s1[i + j] == s2[j])
			j++;
		if (s2[j] == '\0' && j + i <= n)
			return ((char *)s1 + i);
		i++;
	}
	return (0);
}
