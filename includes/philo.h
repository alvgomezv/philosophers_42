/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:41:28 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/20 11:30:14 by alvgomez         ###   ########.fr       */
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
	int				nb_must_eat;
	pthread_mutex_t mutex_eat;
	pthread_mutex_t mutex_fork;
	pthread_mutex_t mutex_print;
}				t_info;

typedef struct s_philo
{
	pthread_t		threads;
	int				philo_id;
	t_info			*inf;
}				t_philo;

//Utils
int		ft_atoi(char *str);
void	ft_free(t_philo **p);
t_info	*inicialize_info(char **argv);
t_philo	**inicialize_philo(char **argv);

#endif

