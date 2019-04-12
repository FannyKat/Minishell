/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinclr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:28:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/12 09:28:36 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinclr(char *s1, char *s2, int xfree)
{
	char	*new;

	if (!(new = ft_strjoin(s1, s2)))
		return (NULL);
	if (xfree == 1)
	{
		free(s1);
		s1 = NULL;
	}
	if (xfree == 2)
	{
		free(s2);
		s2 = NULL;
	}
	if (xfree == 3)
	{
		free(s1);
		free(s2);
		s1 = NULL;
		s2 = NULL;
	}
	return (new);
}
