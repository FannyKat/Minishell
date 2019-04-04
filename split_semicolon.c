/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:22:28 by fcatusse          #+#    #+#             */
/*   Updated: 2019/04/03 16:47:52 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			count_semicolon(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ';')
		i++;
	return (i);
}

int			count_letter(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ';')
		i++;
	return (i);
}

int			count_words(char *str)
{
	int		count;

	count = 0;
	str += count_semicolon(str);
	while (*str)
	{
		count++;
		str += count_letter(str);
		str += count_semicolon(str);
	}
	return (count);
}

char		*ft_strcpy_to_space(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i] && !ft_isblank(src))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		***split_semicolon(char *str)
{
	char	**tab;
	int		i;
	int		count;

	count = count_words(str);
	i = 0;
	tab = malloc(sizeof(tab) * (count + 1));
	str += count_semicolon(str);
	while (*str)
	{
		tab[i] = malloc(sizeof(*tab) * (count_letter(str) + 1));
		ft_strcpy_to_space(tab[i], str);	
		str += count_letter(str);
		str += count_semicolon(str);
	}
	tab[i] = 0;
	return (tab);
}
