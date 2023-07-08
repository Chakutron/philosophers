/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:45:06 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/08 17:30:13 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_parameter(void)
{
	printf("Error in parameters\n");
	exit(0);
}

int	ft_atoi2(char *str, int i, long nb, int neg)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{	
		neg = -1;
		i++;
		error_parameter();
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
		if (nb > INT_MAX || (nb * neg) < INT_MIN)
			error_parameter();
	}
	if (str[i] != '\0')
		error_parameter();
	return (nb * neg);
}

int	ft_atoi(char *str)
{
	return (ft_atoi2(str, 0, 0, 1));
}
