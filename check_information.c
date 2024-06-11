/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:00:33 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 13:01:09 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	ft_check_philo_has_died(t_simulation *info)
{
	int	returnv;

	pthread_mutex_lock(&info->data_mutex);
	if (info->philo_has_died)
		returnv = 1;
	else
		returnv = 0;
	pthread_mutex_unlock(&info->data_mutex);
	return (returnv);
}

int	ft_set_dead_philo_monitor(t_simulation *info, int i)
{
	info->philo_has_died = 1;
	info->params.stop = 1;
	ft_print_dead(info, i, "died\n");
	pthread_mutex_unlock(&info->data_mutex);
	return (1);
}

void	ft_set_forks(t_philosopher *philo, t_fork **first_fork,
			t_fork **second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	return ;
}

int	ft_check_if_full(t_simulation *info, t_philosopher *philo)
{
	int	returnv;

	pthread_mutex_lock(&info->data_mutex);
	if (info->params.stop || philo->is_full)
		returnv = 1;
	else
		returnv = 0;
	pthread_mutex_unlock(&info->data_mutex);
	return (returnv);
}
