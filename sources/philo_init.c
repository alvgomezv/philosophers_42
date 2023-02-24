/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:17:53 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/24 21:02:40 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	arrays_to_zero(t_info *inf)
{
	int	i;

	i = 0;
	inf->mutex_forks = (pthread_mutex_t *)malloc(inf->nb_philo
			* sizeof(pthread_mutex_t));
	if (!inf->mutex_forks)
		ft_error("Failed to allocate memory");
	inf->mutex_eat_die = (pthread_mutex_t *)malloc(inf->nb_philo
			* sizeof(pthread_mutex_t));
	if (!inf->mutex_eat_die)
		ft_error("Failed to allocate memory");
	while (i < inf->nb_philo)
	{
		inf->ate_once[i] = 0;
		inf->forks_locked[i] = 0;
		i++;
	}
}

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
	if (inf->time_to_die <= 0 || inf->time_to_eat <= 0
		|| inf->time_to_sleep <= 0)
		ft_error("Incorrect argument");
	inf->dead = 0;
	inf->ate_once = (int *)malloc(inf->nb_philo * sizeof(int));
	if (!inf->ate_once)
		ft_error("Failed to allocate memory");
	inf->forks_locked = (int *)malloc(inf->nb_philo * sizeof(int));
	if (!inf->forks_locked)
		ft_error("Failed to allocate memory");
	arrays_to_zero(inf);
	return (inf);
}

static void	inizialize_parameters(t_philo **p, char **argv, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		p[i] = (t_philo *)malloc(sizeof(t_philo));
		p[i]->fork_left = i;
		if (nb_philo != 1)
			p[i]->fork_right = (i + 1) % nb_philo;
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
	t_philo	**p;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	if (nb_philo <= 0)
		ft_error("Incorrect argument");
	p = (t_philo **)malloc(nb_philo * sizeof(t_philo *));
	if (!p)
		ft_error("Failed to allocate memory");
	inizialize_parameters(p, argv, nb_philo);
	return (p);
}
