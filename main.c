/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:23:05 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:23:06 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	*ft_check_numbers(char **argv)
{
	int	*numbers;

	numbers = (int *)malloc(5 * sizeof(int));
	if (!numbers)
		return (NULL);
	numbers[0] = ft_check_argument(argv[1]);
	numbers[1] = ft_check_argument(argv[2]);
	numbers[2] = ft_check_argument(argv[3]);
	numbers[3] = ft_check_argument(argv[4]);
	if (argv[5])
		numbers[4] = ft_check_argument(argv[5]);
	else
		numbers[4] = -1;
	return (numbers);
}

int	main(int argc, char **argv)
{
	int	*numbers;

	if (argc != 5 && argc != 6)
		return (ft_write_error("Error: Argument\n", 1));
	numbers = ft_check_numbers(argv);
	if (!numbers)
		return (ft_write_error("Error: Memory allocation\n", 2));
	if (numbers[0] <= 0 || numbers[1] <= 0
		|| numbers[2] <= 0 || numbers[3] <= 0)
	{
		free(numbers);
		return (ft_write_error("Error: Argument\n", 3));
	}
	return (ft_prepare_simulation(numbers));
}
