/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/04 23:36:23 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data2(t_data *data, int i)
{
	data->philo[i].tid = 0;
	data->philo[i].tid2 = 0;
	data->philo[i].left = i;
	data->philo[i].eat_count = data->eat_number;
	if (i == 0)
		data->philo[i].right = data->philo_count - 1;
	else
		data->philo[i].right = i - 1;
	pthread_mutex_init(&data->philo[i].timer_m, NULL);
	data->philo[i].timer = -42;
	pthread_mutex_init(&data->fork_m[i], NULL);
	data->fork[i] = -42;
}

void	init_data(t_data *data)
{
	int				i;
	struct timeval	t;

	i = 0;
	while (i < data->philo_count)
	{
		init_data2(data, i);
		i++;
	}
	pthread_mutex_init(&data->dead_m, NULL);
	pthread_mutex_init(&data->print_m, NULL);
	data->dead = 0;
	data->philo_close = data->philo_count - 1;
	gettimeofday(&t, NULL);
	data->start_time = t.tv_sec * 1000 + t.tv_usec / 1000;
}
