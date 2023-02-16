/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/16 12:26:29 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' '
		|| (str[i] >= 9 && str[i] <= 13))
	i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (nbr);
}

t_philo	*inicialize_arguments(char **argv)
{
	t_philo	*p;

	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
		return (0);
	p->nbr_philo = ft_atoi(argv[1]);
	if (p->nbr_philo <= 0)
		return (0);
	p->philos = (pthread_t *)malloc(p->nbr_philo * sizeof(pthread_t));
	if (!p->philos)
		return (0);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (p->time_to_die <= 0 || p->time_to_eat <= 0 || p->time_to_sleep <= 0)
		return (0);
	if (argv[5])
	{
		p->nbr_must_eat = ft_atoi(argv[5]);
		if (p->nbr_must_eat <= 0)
			return (0);
	}
	return (p);
}

int	main(int argc, char **argv)
{
	t_philo	*p;

	if (argc < 5 || argc > 6)
		return (ft_error("Incorrect number of arguments"));
	p = inicialize_arguments(argv);
	if (!p)
		return (ft_error("Incorrect arguments"));
	return (0);
}
