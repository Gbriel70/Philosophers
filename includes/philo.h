#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}		t_philo_action;

typedef struct s_data
{
	int nbr_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
	pthread_mutex_t *forks;
	pthread_mutex_t *print_mutex;
	short someone_dead;
}				t_data;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	pthread_t thread;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	long long last_meal;
	t_data *data;
}			t_philo;


// UTILS
int print_error(char *message);
short valid_arguments(int ac, char **av);
int ft_atoi(char *str);

// INITS
int init_data(int ac, char **av, t_data *data);
void init_philo_data(t_philo *philos, t_data *data);
int init_mutexes(t_data *data);
void destroy_mutexes(t_data *data);

#endif