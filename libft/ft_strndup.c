/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:02:46 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/20 12:03:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, int n)
{
	char	*dest;

	if (!s1 || !(dest = ft_strnew(n)))
		return (NULL);
	dest = ft_strncpy(dest, s1, n);
	return (dest);
}
