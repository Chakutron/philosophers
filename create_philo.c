/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/02 19:28:10 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *void_data)
{
	t_data			*data;
	pthread_t		tid;
	int				i;
	int				forks;

	data = (t_data *)void_data;
	tid = pthread_self();
	i = 0;
	while (tid != data->philo[i].tid)
		i++;
	update_timer(data, i);
	pthread_mutex_lock(&data->print_m);
	pthread_create(&data->philo[i].tid2, NULL, check_philo, data);
	pthread_mutex_unlock(&data->print_m);
	print_status(data, i, 1);
	while (data->philo[i].eat_count > 0 || data->philo[i].eat_count == -42)
	{
		if (loop_philo(data, i, &forks) == -1)
			break ;
	}
	close_philo(data, i);
	return (NULL);
}
