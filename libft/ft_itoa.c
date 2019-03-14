/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:00:14 by fcatusse          #+#    #+#             */
/*   Updated: 2018/11/12 15:09:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(int n)
{
	int		i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int		ft_is_neg(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char			*ft_itoa(int n)
{
	char		*str;
	int			count;
	long long	nb;

	nb = (int)n;
	count = ft_is_neg(nb) + ft_count(nb);
	if (!(str = ft_strnew(count)))
		return (NULL);
	if (nb == 0)
		*str = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		count--;
		str[count] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
