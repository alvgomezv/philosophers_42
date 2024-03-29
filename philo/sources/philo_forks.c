/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:25:13 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/25 11:53:54 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	mutex_fork(t_philo *p, int fork, int lock)
{
	if (lock == 1)
	{
		if (pthread_mutex_lock(&p->inf->mutex_forks[fork]) != 0)
			ft_error("Failed to lock mutex_forks");
		p->inf->forks_locked[fork] = 1;
		print_time(p, 1);
	}
	else if (lock == 0)
	{
		if (pthread_mutex_unlock(&p->inf->mutex_forks[fork]) != 0)
			ft_error("Failed to unlock mutex_forks");
		p->inf->forks_locked[fork] = 0;
	}
}

void	picking_forks(t_philo *p)
{
	while (1)
	{
		if (p->inf->forks_locked[p->fork_left] == 0
			&& p->inf->forks_locked[p->fork_right] == 0)
		{
			mutex_fork(p, p->fork_left, 1);
			if (p->inf->forks_locked[p->fork_right] == 0)
			{
				mutex_fork(p, p->fork_right, 1);
				break ;
			}
			else if (p->inf->nb_philo == 1)
			{
				while (p->inf->dead == 0)
					usleep(100);
				break ;
			}
			else
				mutex_fork(p, p->fork_left, 0);
		}
	}
	eating(p);
	mutex_fork(p, p->fork_left, 0);
	if (p->inf->nb_philo != 1)
		mutex_fork(p, p->fork_right, 0);
}
