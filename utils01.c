/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:15 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:17 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	ft_strlen(char *string)
{
	int	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	ft_init_create_threads(int *i, int *j, int *result)
{
	*i = 0;
	*j = 0;
	*result = 0;
	return ;
}

long long	ft_get_time(t_simulation *info)
{
	struct timeval	time;
	long long		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time - info->params.current_time);
}

void	ft_print_action(t_simulation *info, int philo_id, char *msg)
{
	long long	time;

	pthread_mutex_lock(&info->data_mutex);
	if (info->full_philos == info->params.number_of_philos)
	{
		pthread_mutex_unlock(&info->data_mutex);
		return ;
	}
	if (info->params.stop)
	{
		pthread_mutex_unlock(&info->data_mutex);
		return ;
	}
	pthread_mutex_lock(&(info->print_mutex));
	time = ft_get_time(info);
	if (!(info->params.stop) && time >= 0)
		printf("%lld %d %s", time, philo_id + 1, msg);
	pthread_mutex_unlock(&(info->print_mutex));
	pthread_mutex_unlock(&info->data_mutex);
}
