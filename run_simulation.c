/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:23:15 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:23:48 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eating_actions(t_philosopher *philo, t_simulation *info,
				t_fork *left_fork, t_fork *right_fork)
{
	long long	temp;

	ft_print_action(info, philo->id, "has taken a fork\n");
	ft_print_action(info, philo->id, "is eating\n");
	pthread_mutex_lock(&info->data_mutex);
	philo->is_eating = 1;
	philo->last_time_eaten = ft_get_time(info);
	temp = info->params.time_to_eat;
	pthread_mutex_unlock(&info->data_mutex);
	usleep(temp);
	philo->times_eaten++;
	pthread_mutex_lock(&info->data_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&info->data_mutex);
	pthread_mutex_unlock(&right_fork->mutex);
	pthread_mutex_unlock(&left_fork->mutex);
}

static void	ft_one_philo(t_simulation *info, t_philosopher *philo)
{
	long long	temp;

	ft_print_action(info, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&info->data_mutex);
	temp = info->params.time_to_die;
	pthread_mutex_unlock(&info->data_mutex);
	usleep(temp + 1000);
	return ;
}

static void	ft_philo_eats(t_philosopher *philo, t_simulation *info)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	ft_set_forks(philo, &first_fork, &second_fork);
	while (!ft_check_philo_has_died(info))
	{
		if (info->params.number_of_philos != 1)
		{
			if (pthread_mutex_lock(&first_fork->mutex) == 0)
			{
				ft_print_action(info, philo->id, "has taken a fork\n");
				if (pthread_mutex_lock(&second_fork->mutex) == 0)
				{
					ft_eating_actions(philo, info, first_fork, second_fork);
					break ;
				}
				else
					pthread_mutex_unlock(&first_fork->mutex);
			}
		}
		else
			return (ft_one_philo(info, philo), (void)0);
	}
	return ;
}

static void	ft_full_philo(t_simulation *info, t_philosopher *philo)
{
	pthread_mutex_lock(&info->data_mutex);
	philo->is_full = 1;
	info->full_philos++;
	pthread_mutex_unlock(&info->data_mutex);
}

void	*ft_run_thread(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*info;

	philo = (t_philosopher *)arg;
	info = philo->simulation;
	philo->last_time_eaten = 0;
	if (philo->id % 2)
		usleep(500);
	while (!ft_check_if_full(info, philo))
	{
		ft_philo_eats(philo, info);
		if (info->params.number_times_to_eat >= 0 && philo->times_eaten
			>= info->params.number_times_to_eat && !philo->is_full)
			ft_full_philo(info, philo);
		if (philo->is_full || info->params.number_of_philos == 1)
			return (NULL);
		ft_print_action(info, philo->id, "is sleeping\n");
		usleep(info->params.time_to_sleep);
		ft_print_action(info, philo->id, "is thinking\n");
		usleep(500);
	}
	return (NULL);
}
