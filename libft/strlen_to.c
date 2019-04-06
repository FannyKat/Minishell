#include "libft.h"

size_t		strlen_to(const char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (i);
}
