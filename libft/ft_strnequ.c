/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:12:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/01/30 18:18:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && i < n)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
		i++;
	}
	return (1);
}
