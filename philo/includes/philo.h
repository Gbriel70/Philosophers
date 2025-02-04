#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

// COLORS
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

// MESSAGES
# define TAKE_FORK_MSG "has taken a fork 🍽️"
# define EAT_MSG "is eating 🍳"
# define SLEEP_MSG "is sleeping 😪"
# define THINK_MSG "is thinking 🤔"
# define DIE_MSG "died ☠️:"

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

typedef struct s_philo t_philo;

typedef struct s_data
{
	t_config config;
	t_mutex mutex;
	t_sim_state sim_state;
	t_philo *philos;
}			t_data;

typedef struct s_philo
{
	int id;
	int time_last_ate;
	int times_eaten;
	short full;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_t philo_pthread;
	t_data *data;
}			t_philo;


// UTILS
int print_error(char *message);
short valid_arguments(int ac, char **av);
int ft_atoi(char *str);

// INIT
t_data *init(int ac, char **av);

// SIMULATION
void simulate(t_data *data);
int print_action(t_philo *philo, t_philo_action action);

// MONITOR
short philo_starved(t_philo *philo);
short all_philos_full(t_philo *philo);

// ROUTINE
void *eating(t_philo *philo);
void take_forks(t_philo *philo);
void set_philo_full(t_philo *philo);
void *sleeping(t_philo *philo);
void *thinking(t_philo *philo);

// TIME
int get_current_time_ms(void);
int calc_elapsed_ms(int start_time_ms);
int calc_elapsed_usec(int start_time_ms);
void ft_usleep(int usec_sleep_time);

// HANDLE ERRORS
void destroy_mutexes(t_mutex *mutex, int nbr_philo, int stage);
short stop_simulation(t_philo *philo, int stop);
short simulation_should_stop(t_data *data);

#endif