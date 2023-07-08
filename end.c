/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/02 16:59:05 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philo[i].timer_m);
		pthread_mutex_destroy(&data->fork_m[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_m);
	pthread_mutex_destroy(&data->print_m);
}
