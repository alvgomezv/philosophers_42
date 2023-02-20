/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:21:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 17:55:56 by alvgomez         ###   ########.fr       */
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
	inf->dead = 0;
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
		p[i]->ate = 0;
		p[i]->over = 0;
		if (argv[5])
		{
			p[i]->nb_must_eat = ft_atoi(argv[5]);
			if (p[i]->nb_must_eat <= 0)
				perror("Incorrect argument");
		}
		else
			p[i]->nb_must_eat = -1;
		i++;
	}
	return (p);
}
void	print_time(t_philo *p, int nb)
{
	struct timeval tv;
	//unsigned long long 	milliseconds;
	
	gettimeofday(&tv, NULL);
	//milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	if(pthread_mutex_lock(&p->inf->mutex_print) != 0)
		perror("Failed to lock mutex_print");
	if (nb == 1)
		printf("%d %d has taken a fork\n", tv.tv_usec, p->philo_id);
	else if (nb == 2)
		printf("%d %d is eating\n", tv.tv_usec, p->philo_id);
	else if (nb == 3)
		printf("%d %d is sleeping\n", tv.tv_usec, p->philo_id);
	else if (nb == 4)
		printf("%d %d is thinking\n", tv.tv_usec, p->philo_id);
	else if (nb == 5)
	{
		printf("%d %d died\n", tv.tv_usec, p->philo_id);
		usleep(10000);
	}
	if(pthread_mutex_unlock(&p->inf->mutex_print) != 0)
		perror("Failed to unlock mutex_print");
}
