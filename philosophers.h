/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:06 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:09 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_simulation	t_simulation;

typedef struct s_params
{
	long long	current_time;
	int			number_of_philos;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			number_times_to_eat;
	int			stop;
}	t_params;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int					id;
	int					times_eaten;
	int					is_eating;
	int					is_full;
	long long			last_time_eaten;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
	t_params			*params;
	struct s_simulation	*simulation;
}	t_philosopher;

typedef struct s_simulation
{
	int				philo_is_full;
	int				philo_has_died;
	int				full_philos;
	int				number_mutexes;
	int				data_mutex_created;
	t_params		params;
	t_philosopher	*philosophers;
	t_fork			*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	int				mutex_created;
	pthread_t		monitor_thread;
}	t_simulation;

//check argument
int			ft_check_argument(char *argument);

//utils
int			ft_strlen(char *string);
void		ft_init_create_threads(int *i, int *j, int *result);
long long	ft_get_time(t_simulation *info);
void		ft_print_action(t_simulation *info, int philo_id, char *msg);
long long	ft_get_current(void);
void		ft_print_dead(t_simulation *info, int philo_id, char *msg);

//error
int			ft_write_error(char *msg, int returnv);

//free memory
void		ft_early_exit(t_simulation *info, int i);
int			ft_free_info(t_simulation *info, int returnv);
void		ft_stop_simulation(t_simulation *info);

//prepare simulation
int			ft_prepare_simulation(int *nmbrs);

//run simulation
void		*ft_monitor(void *arg);
void		*ft_run_thread(void *arg);

//mutexes
int			ft_check_philo_has_died(t_simulation *info);
int			ft_set_dead_philo_monitor(t_simulation *info, int i);
void		ft_set_forks(t_philosopher *philo, t_fork **first_fork,
				t_fork **second_fork);
int			ft_check_if_full(t_simulation *info, t_philosopher *philo);

#endif
