/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:51:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/01/30 15:15:45 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_xlstadd(void *data)
{
	t_list	*x;

	if (!(x = malloc(sizeof(t_list))))
		return (NULL);
	x->content = data;
	x->next = NULL;
	return (x);
}
