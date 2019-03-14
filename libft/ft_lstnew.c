/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:00:48 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/12 10:22:01 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(list->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->size = content_size;
	}
	else
	{
		list->content = NULL;
		list->size = 0;
	}
	list->next = NULL;
	return (list);
}
