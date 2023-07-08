/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/02 17:21:57 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*print_color2(int i)
{
	char	*color;

	if (i % 14 == 0)
		color = "\e[31m";
	else if (i % 14 == 1)
		color = "\e[32m";
	else if (i % 14 == 2)
		color = "\e[33m";
	else if (i % 14 == 3)
		color = "\e[34m";
	else if (i % 14 == 4)
		color = "\e[35m";
	else if (i % 14 == 5)
		color = "\e[36m";
	else if (i % 14 == 6)
		color = "\e[37m";
	else if (i % 14 == 7)
		color = "\e[91m";
	return (color);
}

char	*print_color(int i)
{
	char	*color;

	if ((i % 14 >= 0) && (i % 14 <= 7))
		color = print_color2(i);
	else if (i % 14 == 8)
		color = "\e[92m";
	else if (i % 14 == 9)
		color = "\e[93m";
	else if (i % 14 == 10)
		color = "\e[94m";
	else if (i % 14 == 11)
		color = "\e[95m";
	else if (i % 14 == 12)
		color = "\e[96m";
	else
		color = "\e[97m";
	return (color);
}

void	print_status2(t_data *data, int i, int status)
{
	char	*color;

	color = print_color(i);
	if (status == 1)
		printf("%s%lli\t%i\tis thinking%s\n", color,
			time_passed(data->start_time), i + 1, NC);
	else if (status == 2)
		printf("%s%lli\t%i\thas taken fork\t%i%s\n", color,
			time_passed(data->start_time), i + 1, data->philo[i].left + 1, NC);
	else if (status == 3)
		printf("%s%lli\t%i\thas taken fork\t%i%s\n", color,
			time_passed(data->start_time), i + 1, data->philo[i].right + 1, NC);
	else if (status == 4)
		printf("%s%lli\t%i\tis eating%s\n", color,
			time_passed(data->start_time), i + 1, NC);
	else if (status == 5)
		printf("%s%lli\t%i\tis sleeping%s\n", color,
			time_passed(data->start_time), i + 1, NC);
}

int	print_status(t_data *data, int i, int status)
{
	pthread_mutex_lock(&data->print_m);
	pthread_mutex_lock(&data->dead_m);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->dead_m);
		pthread_mutex_unlock(&data->print_m);
		return (1);
	}
	print_status2(data, i, status);
	pthread_mutex_unlock(&data->dead_m);
	pthread_mutex_unlock(&data->print_m);
	return (0);
}
