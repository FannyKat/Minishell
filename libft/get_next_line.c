/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:02:48 by fcatusse          #+#    #+#             */
/*   Updated: 2019/01/30 18:14:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_error(int fd, char **line)
{
	char			*buff;

	buff = NULL;
	if (fd < 0 || !line || (read(fd, buff, 0) == -1) || BUFF_SIZE < 1)
		return (-1);
	return (0);
}

static int		read_line(char **buffer, char **line)
{
	char			*str;

	str = ft_strchr(*buffer, '\n');
	if (str)
	{
		*line = ft_strsub(*buffer, 0, ft_strlen(*buffer) - ft_strlen(str));
		ft_memcpy(*buffer, str + 1, ft_strlen(str));
		str = NULL;
		return (1);
	}
	return (0);
}

static int		read_buf(int fd, char **buffer, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(*buffer, buf);
		ft_strdel(buffer);
		*buffer = tmp;
		if (read_line(buffer, line) == 1)
			return (1);
	}
	return ((ret == -1) ? -1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*buffer[OPEN_MAX];

	if (check_error(fd, line) == -1)
		return (-1);
	if (!buffer[fd])
		buffer[fd] = ft_memalloc(1);
	if (read_buf(fd, &buffer[fd], line) == 1)
		return (1);
	if (ft_strlen(buffer[fd]) == 0)
		return (0);
	if (read_line(&buffer[fd], line) == 1)
		return (1);
	*line = ft_strdup(buffer[fd]);
	ft_strclr(buffer[fd]);
	return (1);
}
