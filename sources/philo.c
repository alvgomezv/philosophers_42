/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 11:42:31 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void eating(t_philo	*p)
{
	struct timeval tv;
	unsigned long long 	milliseconds;
	
	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("%d %d is eating\n", tv.tv_usec, p->philo_id);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if(pthread_mutex_lock(&p->inf->mutex_eat) != 0)
		perror("Failed to lock mutex");
	eating(p);
	if(pthread_mutex_unlock(&p->inf->mutex_eat) != 0)
		perror("Failed to unlock mutex");
	return (0);
}

void	philo_routine(t_philo **p, char **argv)
{
	int		i;
	t_info	*inf;
	
	i = 0;
	inf = inicialize_info(argv);
	pthread_mutex_init(&inf->mutex_eat, NULL);
	pthread_mutex_init(&inf->mutex_fork, NULL);
	pthread_mutex_init(&inf->mutex_print, NULL);	
	while (i < inf->nb_philo)
	{
		p[i]->inf = inf;
		p[i]->philo_id = i + 1;
		if (pthread_create(&p[i]->threads, NULL, &routine, p[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < inf->nb_philo)
	{
		if (pthread_join(p[i]->threads, NULL) != 0)
			perror("Failed to create thread");
		i++;
	}
	pthread_mutex_destroy(&inf->mutex_eat);
	pthread_mutex_destroy(&inf->mutex_fork);
	pthread_mutex_destroy(&inf->mutex_print);
	free(inf);
}

int	main(int argc, char **argv)
{
	t_philo	**p;
	int		i;

	if (argc < 5 || argc > 6)
		perror("Incorrect number of arguments");
	p = inicialize_philo(argv);
	philo_routine(p, argv);
	ft_free(p);
	//atexit(leaks);
	return (0);
}
