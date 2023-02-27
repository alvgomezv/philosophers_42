/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:31:31 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/25 11:54:24 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_finished(t_philo **p, t_info *inf)
{
	int	i;
	int	all_finish;

	i = 0;
	all_finish = 1;
	while (i < inf->nb_philo)
	{
		if (p[i]->finished != 1)
			all_finish = 0;
		i++;
	}
	return (all_finish);
}

void	*dying_routine(void *arg)
{
	t_philo	*p;
	int		current_eat;

	p = (t_philo *)arg;
	current_eat = p->ate;
	usleep(p->inf->time_to_die * 1000);
	if (p->ate == current_eat)
	{
		pthread_mutex_lock(&p->inf->mutex_eat_die[p->philo_id - 1]);
		pthread_mutex_lock(&p->inf->mutex_die);
		print_time(p, 5);
		p->inf->dead = 1;
		pthread_mutex_unlock(&p->inf->mutex_die);
		pthread_mutex_unlock(&p->inf->mutex_eat_die[p->philo_id - 1]);
	}
	return (0);
}

void	pausing_philo(t_philo *p, long long int sleep)
{
	long long int	wake_up;

	wake_up = time_milliseconds() + sleep;
	while (time_milliseconds() < wake_up)
	{
		if (p->inf->dead == 1)
			break ;
		usleep(10);
	}
}

long long int	time_to_think(t_philo *p)
{
	long long int	time_to_think;

	time_to_think = (p->inf->time_to_die - (time_milliseconds()
				- p->last_meal) - p->inf->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 600)
		time_to_think = 600;
	return (time_to_think);
}	

void	eating(t_philo *p)
{
	pthread_t	t_died;

	pthread_mutex_lock(&p->inf->mutex_eat_die[p->philo_id - 1]);
	p->ate++;
	print_time(p, 2);
	p->last_meal = time_milliseconds();
	pthread_mutex_unlock(&p->inf->mutex_eat_die[p->philo_id - 1]);
	if (p->nb_must_eat != 0)
	{
		if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
			ft_error("Failed to create thread dying");
		if (pthread_detach(t_died) != 0)
			ft_error("Failed to detach thread dying");
	}
	if (p->nb_must_eat != -1)
		p->nb_must_eat--;
	if (p->nb_must_eat == 0)
		p->finished = 1;
	pausing_philo(p, p->inf->time_to_eat);
}
