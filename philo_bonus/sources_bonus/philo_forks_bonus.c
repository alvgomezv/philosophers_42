/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:25:13 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/27 14:50:14 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	picking_forks(t_philo *p)
{
	t_info	*inf;

	inf = p->inf;
	sem_wait(inf->sem_fork);
	print_time(p, 1);
	if (p->inf->nb_philo == 1)
	{
		while (p->inf->dead == 0)
			usleep(100);
	}
	else
	{
		sem_wait(inf->sem_fork);
		print_time(p, 1);
	}
	if (p->inf->dead == 0)
	{
		eating(p);
		sem_post(inf->sem_fork);
		if (p->inf->nb_philo != 1)
			sem_post(inf->sem_fork);
	}
}
