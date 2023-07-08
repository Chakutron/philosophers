/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/04 17:56:17 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo2(t_data *data, int i)
{
	pthread_mutex_lock(&data->print_m);
	if (data->philo[i].eat_count == 0)
	{
		pthread_mutex_unlock(&data->print_m);
		return (1);
	}
	pthread_mutex_unlock(&data->print_m);
	return (0);
}

void	*check_philo(void *void_data)
{
	t_data			*data;
	pthread_t		tid;
	int				i;

	data = (t_data *)void_data;
	tid = pthread_self();
	pthread_mutex_lock(&data->print_m);
	i = 0;
	while (tid != data->philo[i].tid2)
	{
		if (i >= data->philo_count)
			i = 0;
		else
			i++;
	}
	pthread_mutex_unlock(&data->print_m);
	while (!check_dead(data, i))
	{
		if (check_philo2(data, i))
			break ;
		usleep(1000);
	}
	return (NULL);
}
