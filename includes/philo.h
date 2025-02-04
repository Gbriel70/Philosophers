#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

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

typedef struct s_config
{
	int nbr_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nbr_must_eat;
}				t_config;

typedef struct s_mutex
{
	pthread_mutex_t *fork_mtx;
	pthread_mutex_t print_mtx;
	pthread_mutex_t time_ate_mtx;
	pthread_mutex_t philos_full_mtx;
	pthread_mutex_t sim_status_mtx;
}				t_mutex;

typedef struct s_sim_state
{
	int start_time;
	short end_sim;
}				t_sim_state;

typedef struct s_data
{
	t_config config;
	t_mutex mutex;
	t_sim_state sim_state;
}			t_data;

typedef struct s_philo
{
	int id;
	int time_last_ate;
	int times_eaten;
	short full;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_data *data;
}			t_philo;


// UTILS
int print_error(char *message);
short valid_arguments(int ac, char **av);
int ft_atoi(char *str);

// INIT
void init(int ac, char **av);

// TIME
int get_current_time_ms(void);

// HANDLE ERRORS
void destroy_mutexes(t_mutex *mutex, int nbr_philo, int stage);


#endif