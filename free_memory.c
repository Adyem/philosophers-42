/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:27 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:29 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static void	ft_free_philosophers(t_simulation *info)
{
	free(info->philosophers);
	return ;
}

static void	ft_free_forks(t_simulation *info)
{
	int	i;

	i = 0;
	while (i < info->number_mutexes)
	{
		pthread_mutex_destroy(&info->forks[i].mutex);
		i++;
	}
	free(info->forks);
	return ;
}

int	ft_free_info(t_simulation *info, int returnv)
{
	if (info->mutex_created)
		pthread_mutex_destroy(&info->print_mutex);
	if (info->philosophers)
		ft_free_philosophers(info);
	if (info->forks)
		ft_free_forks(info);
	if (info->data_mutex_created)
		pthread_mutex_destroy(&info->data_mutex);
	free(info);
	return (returnv);
}
