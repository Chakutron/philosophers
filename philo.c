/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/08 17:31:22 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&data->philo[i].tid, NULL, philo, data);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc == 5 || argc == 6)
	{
		data.philo_count = ft_atoi(argv[1]);
		if (data.philo_count < 1)
			return (printf("1 philosopher min\n"));
		if (data.philo_count > 200)
			return (printf("200 philosophers max\n"));
		data.time_to_die = ft_atoi(argv[2]);
		data.time_to_eat = ft_atoi(argv[3]);
		data.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data.eat_number = ft_atoi(argv[5]);
		else
			data.eat_number = -42;
		init_data(&data);
		start(&data);
		end_philo(&data);
	}
	else
		printf("%s %s %s\n", MSG1, MSG2, MSG3);
	return (0);
}
