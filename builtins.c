#include "minishell.h"

int		echo_builtin(char **av)
{
	int	i;
	int	j;
	int	flag;
	
	flag = 0;
	if (!av[0])
		return (1);
	else if (av[0][0] == '-' && av[0][1] == 'n')
		flag = 1;
	i = -1;
	flag ? i++ : 0;
	while (av && av[++i])
	{
		j = -1;
		while (av[i] && av[i][++j])
		{
			if (!(av[i][j] == '"'))
				write(1, &av[i][j], 1);
		}
		if (av[i + 1])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
	return (1);
}
