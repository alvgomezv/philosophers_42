/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 17:57:43 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}



int	all_finished(t_philo	**p, t_info *inf)
{
	int	i;
	int all_finish;

	i = 0;
	all_finish = 1;
	while (i < inf->nb_philo)
	{
		if(p[i]->finished != 1)
			all_finish = 0;
		i++;
	}
	return (all_finish);
}

void	sleeping(t_philo *p)
{
	print_time(p, 3);
	usleep(p->inf->time_to_sleep * 1000);
}

void	*dying_routine(void *arg)
{
	t_philo	*p;
	int		round;

	p = (t_philo *)arg;
	round = p->nb_must_eat;
	p->ate = 0;
	usleep(p->inf->time_to_die * 1000);
	while(1)
	{
		if (p->ate == 0 && round == p->nb_must_eat && p->over != 1)
		{
			pthread_mutex_lock(&p->inf->mutex_die);
			print_time(p, 5);
			p->inf->dead = 1;
			sleep(1);
			pthread_mutex_unlock(&p->inf->mutex_die);
			break;
		}
	}
	return (0);
}

void	picking_forks(t_philo *p)
{
	if(pthread_mutex_lock(&p->mutex_forks) != 0)
		perror("Failed to lock mutex_forks");
	
	if(pthread_mutex_unlock(&p->mutex_forks) != 0)
		perror("Failed to unlock mutex_forks");
}

void	eating(t_philo	*p)
{
	pthread_t	t_died;
	
	if(pthread_mutex_lock(&p->inf->mutex_eat) != 0)
		perror("Failed to lock mutex_eat");
	print_time(p, 2);
	p->ate = 1;
	usleep(p->inf->time_to_eat * 1000);
	if (p->nb_must_eat != -1)
		p->nb_must_eat--;
	if (p->nb_must_eat == 0)
		p->over = 1;
	if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
		perror("Failed to create thread dying");
	if (pthread_detach(t_died) != 0)
		perror("Failed to detach thread dying");
	printf("%d -> nb_must_eat: %d\n",p->philo_id, p->nb_must_eat);
	if(pthread_mutex_unlock(&p->inf->mutex_eat) != 0)
		perror("Failed to unlock mutex_eat");
}

void	*routine(void *arg)
{
	t_philo		*p;
	pthread_t	t_died;

	p = (t_philo *)arg;
	if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
			perror("Failed to create thread dying");
	if (pthread_detach(t_died) != 0)
			perror("Failed to detach thread dying");
	while (!p->inf->dead)
	{
		picking_forks(p);
		eating(p);
		sleeping(p);
		if (p->over != 0)
			break;
	}
	if (p->over == 1)
		p->finished = 1;
	printf("%d finished\n",p->philo_id);
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
			perror("Failed to create thread philosopher");
		if (pthread_detach(p[i]->threads) != 0)
			perror("Failed to deatch thread philosopher");
		i++;
	}
	//i = 0;
	while (all_finished(p, inf) == 0)
	{
		if(inf->dead)
		{
			//while (i < inf->nb_philo)
			//{
			//	if (pthread_detach(p[i]->threads) != 0)
			//		perror("Failed to deatch thread philosopher");
			//	i++;
			//}
			break;
		}
	}
	//i = 0;
	//while (i < inf->nb_philo)
	//{
	//	if (pthread_join(p[i]->threads, NULL) != 0)
	//		perror("Failed to join thread philosopher");
	//	//if (pthread_detach(p[i]->threads) != 0)
	//	//	perror("Failed to deatch thread philosopher");
	//	i++;
	//}
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
