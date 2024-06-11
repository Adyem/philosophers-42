/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:41 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:42 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_set_params(t_simulation *info, int *nmbrs)
{
	info->data_mutex_created = 0;
	info->params.stop = 0;
	info->mutex_created = 0;
	info->params.current_time = ft_get_current();
	info->philo_is_full = 0;
	info->full_philos = 0;
	info->philo_has_died = 0;
	info->params.number_of_philos = nmbrs[0];
	info->params.time_to_die = nmbrs[1] * 1000;
	info->params.time_to_eat = nmbrs[2] * 1000;
	info->params.time_to_sleep = nmbrs[3] * 1000;
	info->params.number_times_to_eat = nmbrs[4];
	info->philosophers = NULL;
	info->forks = NULL;
	free(nmbrs);
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
	{
		free(info);
		return (ft_write_error("Error: Mutex initialization\n", 2));
	}
	info->mutex_created = 1;
	return (0);
}

static int	ft_init_forks(t_simulation *info)
{
	int	i;

	if (pthread_mutex_init(&info->data_mutex, NULL) != 0)
	{
		free(info);
		return (ft_write_error("Error: Mutex initialization\n", 2));
	}
	info->data_mutex_created = 1;
	i = 0;
	info->forks = malloc(info->params.number_of_philos * sizeof(t_fork));
	if (!info->forks)
		return (ft_write_error("Error: Memory allocation for forks\n", 2));
	while (i < info->params.number_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i].mutex, NULL))
			return (ft_write_error("Error: Mutex initialization\n", 2));
		info->number_mutexes++;
		i++;
	}
	return (0);
}

static int	ft_init_philosophers(t_simulation *info)
{
	int	i;

	i = 0;
	info->philosophers = malloc(info->params.number_of_philos
			* sizeof(t_philosopher));
	if (!info->philosophers)
		return (ft_write_error("Error: Memory allocation for philos\n", 2));
	while (i < info->params.number_of_philos)
	{
		info->philosophers[i].is_eating = 0;
		info->philosophers[i].simulation = info;
		info->philosophers[i].id = i;
		info->philosophers[i].times_eaten = 0;
		info->philosophers[i].last_time_eaten = 0;
		info->philosophers[i].left_fork = &info->forks[i];
		info->philosophers[i].right_fork = &info->forks[(i + 1)
			% info->params.number_of_philos];
		info->philosophers[i].params = &info->params;
		info->philosophers[i].is_full = 0;
		i++;
	}
	return (0);
}

int	ft_create_threads(t_simulation *info)
{
	int	i;
	int	j;
	int	result;

	ft_init_create_threads(&i, &j, &result);
	while (i < info->params.number_of_philos)
	{
		if (pthread_create(&info->philosophers[i].thread, NULL,
				ft_run_thread, (void *)&info->philosophers[i]) != 0)
		{
			ft_write_error("Error creating philosopher thread\n", 1);
			result = 1;
			break ;
		}
		i++;
	}
	if (result == 1)
		ft_early_exit(info, i);
	return (result);
}

int	ft_prepare_simulation(int *nmbrs)
{
	int				returnv;
	t_simulation	*info;

	info = malloc(sizeof(t_simulation));
	if (!info)
		return (free(nmbrs), ft_write_error("Error: Memory allocation\n", 2));
	info->number_mutexes = 0;
	if (ft_set_params(info, nmbrs))
		return (1);
	if (ft_init_forks(info) | ft_init_philosophers(info))
	{
		ft_free_info(info, 1);
		return (1);
	}
	if (pthread_create(&(info->monitor_thread), NULL, ft_monitor,
			(void *)info) != 0)
	{
		ft_free_info(info, 1);
		return (1);
	}
	returnv = ft_create_threads(info);
	pthread_join(info->monitor_thread, NULL);
	return (ft_free_info(info, returnv));
}
