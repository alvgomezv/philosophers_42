/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/25 11:55:02 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo		*p;
	pthread_t	t_died;

	p = (t_philo *)arg;
	if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
		ft_error("Failed to create thread dying");
	if (pthread_detach(t_died) != 0)
		ft_error("Failed to detach thread dying");
	while (!p->inf->dead)
	{
		if (p->finished == 0)
			picking_forks(p);
		if (p->finished == 0 && p->inf->dead == 0)
		{
			print_time(p, 3);
			pausing_philo(p, p->inf->time_to_sleep);
		}
		if (p->finished == 0 && p->inf->dead == 0)
			pausing_philo(p, time_to_think(p));
		else
			break ;
	}
	return (0);
}

static void	create_threads(t_philo **p, t_info *inf)
{
	int		i;

	i = 0;
	while (i < inf->nb_philo)
	{
		p[i]->inf = inf;
		p[i]->philo_id = i + 1;
		if (pthread_create(&p[i]->threads, NULL, &routine, p[i]) != 0)
			ft_error("Failed to create thread philosopher");
		i++;
	}
	i = 0;
	while (i < inf->nb_philo)
	{
		if (pthread_join(p[i]->threads, NULL) != 0)
			perror("Failed to join thread philosopher");
		i++;
	}
}

void	philo_routine(t_philo **p, char **argv)
{
	int		i;
	t_info	*inf;

	i = 0;
	inf = inicialize_info(argv);
	inicialize_mutex(p, inf);
	create_threads(p, inf);
	while (all_finished(p, inf) == 0)
	{
		if (inf->dead)
		{
			pthread_mutex_lock(&inf->mutex_print);
			break ;
		}
	}
	pthread_mutex_unlock(&inf->mutex_print);
	destroy_mutex(p, inf);
	free(inf);
}

int	main(int argc, char **argv)
{
	t_philo	**p;
	int		i;

	if (argc < 5 || argc > 6)
		ft_error("Incorrect number of arguments");
	else
	{
		p = inicialize_philo(argv);
		philo_routine(p, argv);
		ft_free(p);
	}
	return (0);
}
