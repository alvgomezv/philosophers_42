/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:17:53 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/27 14:58:31 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

t_info	*inicialize_info(char **argv)
{
	t_info	*inf;

	inf = (t_info *)malloc(sizeof(t_info));
	if (!inf)
		ft_error("Failed to allocate memory");
	inf->nb_philo = ft_atoi(argv[1]);
	inf->time_to_die = ft_atoi(argv[2]);
	inf->time_to_eat = ft_atoi(argv[3]);
	inf->time_to_sleep = ft_atoi(argv[4]);
	if (inf->time_to_die < 0 || inf->time_to_eat < 0
		|| inf->time_to_sleep < 0)
		ft_error("Incorrect argument");
	inf->dead = 0;
	return (inf);
}

static void	aux_init(t_philo **p, char **argv, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		p[i] = (t_philo *)malloc(sizeof(t_philo));
		p[i]->philo_id = i + 1;
		p[i]->ate = 0;
		p[i]->finished = 0;
		if (argv[5])
		{
			p[i]->nb_must_eat = ft_atoi(argv[5]);
			if (p[i]->nb_must_eat <= 0)
				ft_error("Incorrect argument");
		}
		else
			p[i]->nb_must_eat = -1;
		i++;
	}
}

t_philo	**inicialize_philo(char **argv)
{
	int		i;
	t_philo	**p;
	int		nb_philo;

	i = 0;
	nb_philo = ft_atoi(argv[1]);
	if (nb_philo <= 0)
		ft_error("Incorrect argument");
	p = (t_philo **)malloc(nb_philo * sizeof(t_philo *));
	if (!p)
		ft_error("Failed to allocate memory");
	aux_init(p, argv, nb_philo);
	return (p);
}
