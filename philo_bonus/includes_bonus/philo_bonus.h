/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:41:28 by alvgomez          #+#    #+#             */
/*   Updated: 2023/02/27 14:49:53 by alvgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/errno.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_die;
}				t_info;

typedef struct s_philo
{
	t_info				*inf;
	int					philo_id;
	int					nb_must_eat;
	pid_t				pid;
	int					ate;
	int					finished;
	long long int		last_meal;
	sem_t				*sem_eat_die;
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
t_philo			**inicialize_philo(char **argv);
t_info			*inicialize_info(char **argv);

//Stages
void			pausing_philo(t_philo *p, long long int sleep);
long long int	time_to_think(t_philo *p);
void			*dying_routine(void *arg);
void			eating(t_philo	*p);

//Semaphores
void			open_semaphore(t_info *inf, t_philo **p);
void			close_semaphore(t_info *inf, t_philo **p);

#endif
