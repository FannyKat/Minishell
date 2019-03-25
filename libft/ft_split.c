/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:50:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/03/25 16:11:27 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			count_sep(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	return (i);
}

int			count_letter(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isblank(str[i]))
		i++;
	return (i);
}

int			count_words(char *str)
{
	int		count;

	count = 0;
	if (!str)
		return (0);
	str += count_sep(str);
	while (*str)
	{
		count++;
		str += count_letter(str);
		str += count_sep(str);
	}
	return (count);
}

char		*ft_strcpy_to_space(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src && src[i] && !ft_isblank(src[i]))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		**ft_split(char *s)
{
	int		words_count;
	char	**tab;
	int		i;

	i = 0;
	words_count = count_words(s);
	if (!s)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (words_count + 1))))
		return (NULL);
	s += count_sep(s);
	while (*s)
	{
		tab[i] = malloc(sizeof(char) * count_letter(s) + 1);
		ft_strcpy_to_space(tab[i], s);
		s += count_letter(s);
		s += count_sep(s);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
