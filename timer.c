/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/02 16:50:09 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_passed(long long timer)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000 - timer);
}

void	update_timer(t_data *data, int i)
{
	struct timeval	t;

	pthread_mutex_lock(&data->philo[i].timer_m);
	gettimeofday(&t, NULL);
	data->philo[i].timer = t.tv_sec * 1000 + t.tv_usec / 1000;
	pthread_mutex_unlock(&data->philo[i].timer_m);
}
