/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:41:28 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/24 21:22:55 by alvgomez         ###   ########.fr       */
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
	int				*ate_once;
	int				*forks_locked;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	*mutex_eat_die;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_print;
}				t_info;

typedef struct s_philo
{
	pthread_t			threads;
	t_info				*inf;
	int					philo_id;
	int					nb_must_eat;
	int					fork_left;
	int					fork_right;
	int					ate;
	int					finished;
	long long int		last_meal;
}				t_philo;

//Utils
void			ft_error(char *str);
long long int	time_milliseconds(void);
int				ft_atoi(char *str);
void			ft_free(t_philo **p);
void			print_time(t_philo *p, int nb);

//Forks
void			picking_forks(t_philo *p);

//Init
t_info			*inicialize_info(char **argv);
t_philo			**inicialize_philo(char **argv);

//Stages
int				all_finished(t_philo **p, t_info *inf);
//int					all_eaten(t_philo	*p);
void			pausing_philo(t_philo *p, long long int sleep);
long long int	time_to_think(t_philo *p);
void			*dying_routine(void *arg);
void			eating(t_philo	*p);

//Mutex
void			inicialize_mutex(t_philo **p, t_info *inf);
void			destroy_mutex(t_philo **p, t_info *inf);


#endif

