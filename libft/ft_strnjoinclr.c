#include "libft.h"

char	*ft_strnjoinclr(char *s1, char *s2, size_t n, int free_s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + n)))
		return (NULL);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	free(s1);
	s1 = NULL;
	ft_strncat(str, s2, n);
	if (free_s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (str);
}
