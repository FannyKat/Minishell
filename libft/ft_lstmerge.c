/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:09:05 by fcatusse          #+#    #+#             */
/*   Updated: 2019/02/12 17:12:55 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstmerge(t_list *list1, t_list *list2)
{
	t_list	*begin;

	begin = list1;
	if (!list1 || !list2)
		return ;
	while (list1->next)
		list1 = list1->next;
	list1->next = list2;
}
