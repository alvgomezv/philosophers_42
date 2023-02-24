/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:35:02 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/24 19:35:32 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	inicialize_mutex(t_philo **p, t_info *inf)
{
	int	i;

	i = 0;
	pthread_mutex_init (&inf->mutex_print, NULL);
	pthread_mutex_init (&inf->mutex_die, NULL);
	while (i < inf->nb_philo)
	{
		pthread_mutex_init(&inf->mutex_forks[i], NULL);
		pthread_mutex_init (&inf->mutex_eat_die[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_philo **p, t_info *inf)
{
	int	i;

	i = 0;
	pthread_mutex_destroy (&inf->mutex_print);
	pthread_mutex_destroy (&inf->mutex_die);
	while (i < inf->nb_philo)
	{
		pthread_mutex_destroy(&inf->mutex_forks[i]);
		pthread_mutex_destroy (&inf->mutex_eat_die[i]);
		i++;
	}
}