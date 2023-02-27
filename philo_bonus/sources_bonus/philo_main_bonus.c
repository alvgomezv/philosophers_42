/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:28:34 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/27 14:58:59 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	routine(t_philo *p)
{
	pthread_t	t_died;
	t_info		*inf;

	inf = p->inf;
	if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
		ft_error("Failed to create thread dying");
	if (pthread_detach(t_died) != 0)
		ft_error("Failed to detach thread dying");
	while (!inf->dead)
	{
		if (p->finished == 0)
			picking_forks(p);
		if (p->finished == 0 && inf->dead == 0)
		{
			print_time(p, 3);
			pausing_philo(p, inf->time_to_sleep);
		}
		if (p->finished == 0 && inf->dead == 0)
			pausing_philo(p, time_to_think(p));
		else
			break ;
	}
	if (inf->dead)
		exit(1);
	exit(0);
}

void	ft_exit(t_philo **p, t_info *inf)
{
	int	i;
	int	res;

	i = 0;
	while (i < inf->nb_philo)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			i = 0;
			while (i < inf->nb_philo)
			{
				kill(p[i]->pid, 15);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	processes(t_philo **p, char **argv)
{
	int		i;
	t_info	*inf;

	i = 0;
	inf = inicialize_info(argv);
	open_semaphore(inf, p);
	while (i < inf->nb_philo)
	{
		p[i]->inf = inf;
		p[i]->pid = fork();
		if (p[i]->pid < 0)
			ft_error("Failed creating process");
		else if (p[i]->pid == 0)
			routine(p[i]);
		i++;
	}
	ft_exit(p, inf);
	close_semaphore(inf, p);
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
		processes(p, argv);
		ft_free(p);
	}
	return (0);
}
