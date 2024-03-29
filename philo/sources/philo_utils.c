/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:21:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/25 11:56:30 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

long long int	time_milliseconds(void)
{
	struct timeval	tv;
	long long int	milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (milliseconds);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	nbr;

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
	if (nbr > 2147483637)
		return (-1);
	return (nbr);
}

void	ft_free(t_philo **p)
{
	int	i;
	int	j;
	int	nb_philo;

	i = 0;
	j = 0;
	nb_philo = p[0]->inf->nb_philo;
	free(p[0]->inf->mutex_forks);
	free(p[0]->inf->ate_once);
	free(p[0]->inf->forks_locked);
	while (i < nb_philo)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	print_time(t_philo *p, int nb)
{
	pthread_mutex_lock(&p->inf->mutex_print);
	if (!p->inf->dead)
	{
		if (nb == 5)
			printf("%llu %d died\n", time_milliseconds(), p->philo_id);
		else if (nb == 1)
			printf("%llu %d has taken a fork\n",
				time_milliseconds(), p->philo_id);
		else if (nb == 2)
			printf("%llu %d is eating\n", time_milliseconds(), p->philo_id);
		else if (nb == 3)
			printf("%llu %d is sleeping\n", time_milliseconds(), p->philo_id);
		else if (nb == 4)
			printf("%llu %d is thinking\n", time_milliseconds(), p->philo_id);
	}
	pthread_mutex_unlock(&p->inf->mutex_print);
}
