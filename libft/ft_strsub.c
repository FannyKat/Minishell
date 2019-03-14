/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:14:13 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/14 17:16:09 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*copy;
	int			i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (NULL);
	if (!(copy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	copy[len] = '\0';
	while (len--)
	{
		copy[i] = s[start];
		i++;
		start++;
	}
	return (copy);
}
