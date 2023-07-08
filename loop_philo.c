/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:29:36 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/04 23:34:39 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_even(t_data *data, int i, int *forks)
{
	pthread_mutex_lock(&data->fork_m[data->philo[i].left]);
	if (data->fork[data->philo[i].left] != i)
	{
		data->philo[i].print += print_status(data, i, 2);
		(*forks)++;
		pthread_mutex_lock(&data->fork_m[data->philo[i].right]);
		if (data->fork[data->philo[i].right] != i)
		{
			data->philo[i].print += print_status(data, i, 3);
			(*forks)++;
		}
		else
		{
			pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
			pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
			usleep(1000);
		}
	}
	else
	{
		pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
		usleep(1000);
	}
}

void	philo_odd(t_data *data, int i, int *forks)
{
	pthread_mutex_lock(&data->fork_m[data->philo[i].right]);
	if (data->fork[data->philo[i].right] != i)
	{
		data->philo[i].print += print_status(data, i, 3);
		(*forks)++;
		pthread_mutex_lock(&data->fork_m[data->philo[i].left]);
		if (data->fork[data->philo[i].left] != i)
		{
			data->philo[i].print += print_status(data, i, 2);
			(*forks)++;
		}
		else
		{
			pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
			pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
			usleep(1000);
		}
	}
	else
	{
		pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
		usleep(1000);
	}
}

void	eat_and_sleep(t_data *data, int i)
{
	data->fork[data->philo[i].left] = i;
	data->fork[data->philo[i].right] = i;
	update_timer(data, i);
	data->philo[i].print += print_status(data, i, 4);
	usleep(data->time_to_eat * 1000);
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
		pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
		pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
	}
	pthread_mutex_lock(&data->print_m);
	if (data->philo[i].eat_count != -42)
		data->philo[i].eat_count -= 1;
	pthread_mutex_unlock(&data->print_m);
	data->philo[i].print += print_status(data, i, 5);
	usleep(data->time_to_sleep * 1000);
	data->philo[i].print += print_status(data, i, 1);
}

void	close_philo(t_data *data, int i)
{
	while (1)
	{
		pthread_mutex_lock(&data->print_m);
		if (data->philo_close == i)
		{
			data->philo_close -= 1;
			pthread_mutex_unlock(&data->print_m);
			pthread_join(data->philo[i].tid2, NULL);
			break ;
		}
		pthread_mutex_unlock(&data->print_m);
		usleep(1000);
	}
}

int	loop_philo(t_data *data, int i, int *forks)
{
	*forks = 0;
	data->philo[i].print = 0;
	if (data->philo[i].left != data->philo[i].right)
	{
		if (i % 2 == 0)
			philo_even(data, i, forks);
		else
			philo_odd(data, i, forks);
	}
	else
		return (-1);
	if (data->philo[i].print > 0)
	{
		if (*forks == 2)
		{
			pthread_mutex_unlock(&data->fork_m[data->philo[i].left]);
			pthread_mutex_unlock(&data->fork_m[data->philo[i].right]);
		}
		return (-1);
	}
	if (*forks == 2)
		eat_and_sleep(data, i);
	if (data->philo[i].print > 0)
		return (-1);
	return (0);
}
