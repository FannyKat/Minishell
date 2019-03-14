/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:58:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/12 10:22:41 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*fresh_new;

	tmp = f(lst);
	if (!(new = ft_lstnew(tmp->content, tmp->size)))
		return (NULL);
	fresh_new = new;
	while (lst->next)
	{
		tmp = f(lst->next);
		if (!(new->next = ft_lstnew(tmp->content, tmp->size)))
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (fresh_new);
}
