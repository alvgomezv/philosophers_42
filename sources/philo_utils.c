/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:21:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 11:42:34 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	ft_free(t_philo **p)
{
	int	i;
	int	nb_philo;
	
	i = 0;
	nb_philo = p[0]->inf->nb_philo;
	while (i < nb_philo)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

t_info	*inicialize_info(char **argv)
{
	t_info	*inf;

	inf = (t_info *)malloc(sizeof(t_info));
	if (!inf)
		perror("Failed to allocate memory");
	inf->nb_philo = ft_atoi(argv[1]);
	inf->time_to_die = ft_atoi(argv[2]);
	inf->time_to_eat = ft_atoi(argv[3]);
	inf->time_to_sleep = ft_atoi(argv[4]);
	if (inf->time_to_die <= 0 || inf->time_to_eat <= 0 || inf->time_to_sleep <= 0)
		perror("Incorrect argument");
	if (argv[5])
	{
		inf->nb_must_eat = ft_atoi(argv[5]);
		if (inf->nb_must_eat <= 0)
			perror("Incorrect argument");
	}
	return (inf);
}

t_philo	**inicialize_philo(char **argv)
{
	t_philo	**p;
	int		nb_philo;
	int 	i;

	i = 0;
	nb_philo = ft_atoi(argv[1]);
	if (nb_philo <= 0)
		perror("Incorrect argument");
	p = (t_philo **)malloc(nb_philo * sizeof(t_philo *));
	if (!p)
		perror("Failed to allocate memory");
	while (i < nb_philo)
	{
		p[i] = (t_philo *)malloc(sizeof(t_philo));
		i++;
	}
	return (p);
}