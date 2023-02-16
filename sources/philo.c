/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/16 19:38:08 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
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

t_philo	*inicialize_philo(char **argv)
{
	t_philo	*p;

	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
		perror("Failed to allocate memory");
	p->nb_philo = ft_atoi(argv[1]);
	if (p->nb_philo <= 0)
		perror("Incorrect argument");
	p->threads = (pthread_t *)malloc(p->nb_philo * sizeof(pthread_t));
	if (!p->threads)
		perror("Failed to allocate memory");
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (p->time_to_die <= 0 || p->time_to_eat <= 0 || p->time_to_sleep <= 0)
		perror("Incorrect argument");
	if (argv[5])
	{
		p->nb_must_eat = ft_atoi(argv[5]);
		if (p->nb_must_eat <= 0)
			perror("Incorrect argument");
	}
	return (p);
}

void eating(t_philo	*p)
{
	struct timeval tv;
	unsigned long long 	milliseconds;
	
	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("%d %d is eating\n", tv.tv_usec, p->philo);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if(pthread_mutex_lock(&p->mutex) != 0)
		perror(strerror(errno));
	eating(p);
	if(pthread_mutex_unlock(&p->mutex) != 0)
		perror(strerror(errno));
	return (0);
}

void	philo_routine(t_philo *p)
{
	int				i;
	t_philo			**aux;
	
	i = 0;
	//aux = (t_philo **)malloc(p->forks * sizeof(t_philo *));
	//if (!aux)
	//	perror("Failed to allocate memory");
	pthread_mutex_init(&p->mutex, NULL);
	while (i < p->nb_philo)
	{
		//if (!aux[i])
		//aux[i] = (t_philo *)malloc(sizeof(t_philo));
		//	perror("Failed to allocate memory");
		//*aux[i] = *p;
		//aux[i]->philo = i + 1;
		if (pthread_create(&p->threads[i], NULL, &routine, p) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < p->nb_philo)
	{
		if (pthread_join(p->threads[i], NULL) != 0)
			perror("Failed to create thread");
		i++;
	}
	pthread_mutex_destroy(&p->mutex);
	//free(aux);
}

int	main(int argc, char **argv)
{
	t_philo	*p;
	int		i;

	if (argc < 5 || argc > 6)
		perror("Incorrect number of arguments");
	p = inicialize_philo(argv);
	philo_routine(p);
	free(p->threads);
	free(p);
	//atexit(leaks);
	return (0);
}
