/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:35:02 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/27 14:51:19 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	open_semaphore(t_info *inf, t_philo **p)
{
	int		i;
	char	str[2];

	i = 0;
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/die");
	inf->sem_fork = sem_open("/fork", O_CREAT, 0644, inf->nb_philo);
	inf->sem_print = sem_open("/print", O_CREAT, 0644, 1);
	inf->sem_die = sem_open("/die", O_CREAT, 0644, 1);
	if (inf->sem_fork == SEM_FAILED || inf->sem_print == SEM_FAILED
		|| inf->sem_die == SEM_FAILED)
		ft_error("Failed creating semaphore");
	while (i < inf->nb_philo)
	{
		str[0] = (char)i;
		str[1] = '\0';
		sem_unlink(str);
		p[i]->sem_eat_die = sem_open(str, O_CREAT, 0644, 1);
		if (p[i]->sem_eat_die == SEM_FAILED)
			ft_error("Failed creating semaphore");
		i++;
	}
}

void	close_semaphore(t_info *inf, t_philo **p)
{
	int		i;
	char	str[2];

	i = 0;
	sem_close(inf->sem_fork);
	sem_close(inf->sem_print);
	sem_close(inf->sem_die);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/die");
	while (i < inf->nb_philo)
	{
		str[0] = (char)i;
		str[1] = '\0';
		sem_unlink(str);
		sem_close(p[i]->sem_eat_die);
		i++;
	}
}
