/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:35 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:36 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	ft_stop_simulation(t_simulation *info)
{
	int	i;

	i = 0;
	while (i < info->params.number_of_philos)
	{
		pthread_join(info->philosophers[i].thread, NULL);
		i++;
	}
	return ;
}

int	ft_check_dead_philos(t_simulation *info)
{
	int			i;
	long long	current_time;

	i = 0;
	while (i < info->params.number_of_philos)
	{
		pthread_mutex_lock(&info->data_mutex);
		current_time = ft_get_time(info);
		if (info->philosophers[i].is_full)
		{
			i++;
			pthread_mutex_unlock(&info->data_mutex);
			continue ;
		}
		if ((!info->philosophers[i].is_eating && (current_time * 1000
					- info->philosophers[i].last_time_eaten * 1000)
				> info->params.time_to_die))
			return (ft_set_dead_philo_monitor(info, i));
		pthread_mutex_unlock(&info->data_mutex);
		i++;
	}
	return (0);
}

int	ft_check_simulation_status(t_simulation *info)
{
	pthread_mutex_lock(&info->data_mutex);
	if (info->full_philos == info->params.number_of_philos)
	{
		info->params.stop = 1;
		pthread_mutex_unlock(&info->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->data_mutex);
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_simulation	*info;

	info = (t_simulation *)arg;
	usleep(20000);
	while (!info->params.stop)
	{
		if (ft_check_dead_philos(info))
		{
			ft_stop_simulation(info);
			return (NULL);
		}
		if (ft_check_simulation_status(info))
		{
			ft_stop_simulation(info);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
