/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:23:00 by bvangene          #+#    #+#             */
/*   Updated: 2024/06/11 11:23:01 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_write_error(char *msg, int returnv)
{
	write (2, msg, ft_strlen(msg));
	return (returnv);
}
