#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <pthread.h>

// MACROS
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
}   t_philo_action;

typedef struct config
{
    int nbr_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_must_eat;
}   t_config;

typedef struct s_semaphores
{
    sem_t *forks;
    sem_t *table;
    sem_t *print;
    sem_t *death;
    sem_t *full;
    sem_t *stop;
    sem_t *sem_state;
}   t_semaphores;

typedef struct s_minitor
{
    short sim_stop;
    int start_time;
}           t_monitor;

typedef struct s_philo t_philo;

typedef struct s_data
{
    t_config *config;
    t_semaphores *semaphores;
    t_monitor *monitor;
    t_philo *philo;
    pid_t *philo_pid;
}           t_data;

typedef struct s_philo
{
    int id;
    int time_last_ate;
    int times_eaten;
    pthread_t self_monitor;
    char *sem_state_name;
    t_data *data;
}   t_philo;

// CHECK_UTILS
int ft_atoi(char *str);
short valid_arguments(int ac, char **av);
int print_error(char *message);

// INIT
t_data *init(int ac, char **av);

// HANDLE_ERRORS
void error_exit(char *message, t_data *data, int stage);

// TIME_UTILS
int get_current_time_ms(void);
int calc_elapsed_ms(int start_time_ms);
int calc_elapsed_usec(int start_time_ms);
void ft_usleep(int usec_sleep_time);

// UTILS
char *ft_utoa(int i);
char *ft_strjoin(char *str, char *str2);

// FINISH
void close_shared_semaphores(t_data *data);
void unlink_shared_semaphores(void);

#endif