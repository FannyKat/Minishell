/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:41:04 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/08 11:41:15 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		strlen_to(const char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (i);
}
