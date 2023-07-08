/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiboub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:23:59 by mchiboub          #+#    #+#             */
/*   Updated: 2023/07/02 19:28:50 by mchiboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		tid;
	pthread_t		tid2;
	int				left;
	int				right;
	pthread_mutex_t	timer_m;
	long long		timer;
	int				eat_count;
	int				dead;
	int				print;
}				t_philo;

typedef struct s_data
{
	t_philo			philo[200];
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	pthread_mutex_t	fork_m[200];
	int				fork[200];
	long long		start_time;
	pthread_mutex_t	dead_m;
	int				dead;
	pthread_mutex_t	print_m;
	int				philo_close;
}			t_data;

# define MSG1 "USAGE: ./philo number_of_philosophers"
# define MSG2 "time_to_die time_to_eat time_to_sleep"
# define MSG3 "[number_of_times_each_philosopher_must_eat]"
# define NC "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"

int			ft_atoi(char *str);
void		error_parameter(void);
void		init_data(t_data *data);
void		*philo(void *void_data);
int			loop_philo(t_data *data, int i, int *forks);
void		*check_philo(void *void_data);
void		update_timer(t_data *data, int i);
int			check_dead(t_data *data, int i);
char		*print_color(int i);
int			print_status(t_data *data, int i, int status);
long long	time_passed(long long timer);
void		close_philo(t_data *data, int i);
void		end_philo(t_data *data);

#endif
