/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:41:28 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 15:30:36 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/errno.h>

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	pthread_mutex_t *mutex_forks;
	pthread_mutex_t mutex_eat;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_die;
}				t_info;

typedef struct s_philo
{
	pthread_t		threads;
	t_info			*inf;
	int				philo_id;
	int				nb_must_eat;
	int				fork_left;
	int				fork_right;
	int				ate;
	int				over;
	int				finished;
}				t_philo;

//Utils
int		ft_atoi(char *str);
void	ft_free(t_philo **p);
t_info	*inicialize_info(char **argv);
t_philo	**inicialize_philo(char **argv);
void	print_time(t_philo *p, int nb);

#endif

