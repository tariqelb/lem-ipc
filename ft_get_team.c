#include "lemipc.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}


int	ft_putint(int nbr)
{
	char	tab[10];
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (nbr <= 0)
	{
		if (nbr == 0)
			return (ft_putstr("0"));
		else if (nbr == -2147483648)
			return (ft_putstr("-2147483648"));
		else
			nb = nb + ft_putstr("-");
		nbr = nbr * -1;
	}
	while (nbr)
	{
		tab[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	nb = nb + i;
	while (i)
		write(1, &tab[--i], 1);
	return (nb);
}


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

int	ft_get_team(int ac, char *av, t_player *player)
{
	//ft_putstr("ft_get_team\n");
	int	i;
	int 	team;
	int	is_a_number;

	if (ac != 2)
	{
		write(2, "Lemipc : Missing player team\n", 29);
		write(2, "Usage: ./lemipc [1 - N]\n", 24);
		return (-1);
	}

	
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
		return (-1);
	}
	team = ft_atoi(av);
	if (team > 0)
	{
		player->team_id = team;
		return (team);
	}
	write(2, "Lemipc : Wrong team id\n", 23);
	return (-1);
}
