/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/04 17:51:48 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead2(t_data *data, int i)
{
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_m);
	pthread_mutex_unlock(&data->philo[i].timer_m);
}

int	check_dead(t_data *data, int i)
{
	char		*color;
	long long	timer;

	pthread_mutex_lock(&data->philo[i].timer_m);
	timer = time_passed(data->philo[i].timer);
	if (timer >= data->time_to_die && data->philo[i].timer != -42
		&& data->philo[i].eat_count != 0)
	{
		color = print_color(i);
		pthread_mutex_lock(&data->dead_m);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->dead_m);
			pthread_mutex_unlock(&data->philo[i].timer_m);
			return (1);
		}
		else if (data->dead == 0)
			printf("%s%lli\t%i\tdied%s\n", color, time_passed(data->start_time),
				i + 1, NC);
		check_dead2(data, i);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].timer_m);
	return (0);
}
