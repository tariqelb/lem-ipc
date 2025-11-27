#include "lemipc.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nbr;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\n' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (str[i] - 48);
		i++;
	}
	return (nbr * sign);
}

int	ft_get_team(char *av)
{
	int	i;
	int 	team;
	int	is_a_number;
	
	i = 0;
	team = 0;
	is_a_number = 1;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
		{
			is_a_number = 0;
			break;
		}
	}
	if (is_a_number == 0)
	{
		write(2, "Fisrt argument should be pure number from 1 to N\n", 49);
		return (0);
	}
	team = ft_atoi(av);
	if (team > 0)	
		return (team);
	return (0);
}
