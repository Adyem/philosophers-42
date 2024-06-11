/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:22:50 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:22:52 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_initialize_values(long *check, int *i, int *sign)
{
	*check = 0;
	*i = 0;
	*sign = 1;
}

static int	ft_check_value(char *input)
{
	long	check;
	int		i;
	int		sign;

	ft_initialize_values(&check, &i, &sign);
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (3);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (3);
			i++;
		}
		else
			return (3);
	}
	return (0);
}

static int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || ((str[i] >= '\t') && (str[i] <= '\r')))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

int	ft_check_argument(char *argument)
{
	if (ft_check_value(argument))
		return (-1);
	return (ft_atoi(argument));
}
