/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:20 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:21 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_get_current(void)
{
	struct timeval	time;
	long long		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
	return (current_time);
}

void	ft_print_dead(t_simulation *info, int philo_id, char *msg)
{
	long long	time;

	pthread_mutex_lock(&(info->print_mutex));
	time = ft_get_time(info);
	printf("%lld %d %s", time, philo_id + 1, msg);
	pthread_mutex_unlock(&(info->print_mutex));
}

void	ft_early_exit(t_simulation *info, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(info->philosophers[j].thread, NULL);
		j++;
	}
}
