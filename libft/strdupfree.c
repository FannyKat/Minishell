#include "libft.h"

char		*strdupfree(char *s1)
{
	int	i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	ft_strdel(&s1);
	dest[i] = '\0';
	return (dest);
}
