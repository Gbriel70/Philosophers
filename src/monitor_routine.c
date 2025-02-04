#include "../includes/philo.h"

static int	time_hungry(t_philo *philo);
static short philo_full(t_philo *philo);

short philo_starved(t_philo *philo)
{
    short starved_state;
    int i;

    starved_state = FALSE;
    i = -1;
    while(++i < philo->data->config.nbr_philo  && !stop_simulation(philo, 0))
    {
        pthread_mutex_lock(&philo->data->mutex.time_ate_mtx);
        if (time_hungry(&philo[i]) > philo->data->config.time_to_die)
        {
            print_action(&philo[i], DIE);
            starved_state = TRUE;
        }
        pthread_mutex_unlock(&philo->data->mutex.time_ate_mtx);
        if (starved_state)
            break ;
    }
    return (starved_state);
}

static int time_hungry(t_philo *philo)
{
    int current_time;
    int time_hungry;

    current_time = calc_elapsed_ms(philo->data->sim_state.start_time);
    time_hungry = current_time - philo->time_last_ate;
    return (time_hungry);
}

static short philo_full(t_philo *philo)
{
    short is_full;

    is_full = FALSE;
    pthread_mutex_lock(&philo->data->mutex.philos_full_mtx);
    if (philo->full)
        is_full = TRUE;
    pthread_mutex_unlock(&philo->data->mutex.philos_full_mtx);
    return (is_full);
}

short all_philos_full(t_philo *philo)
{
    short full_state;
    int i;
    int qtd_philos_full;

    full_state = FALSE;
    i = -1;
    qtd_philos_full = 0;
    while (++i < philo->data->config.nbr_philo && !stop_simulation(philo, 0))
    {
        if (philo_full(&philo[i]))
            qtd_philos_full++;
    }
    if (qtd_philos_full == philo->data->config.nbr_philo)
        full_state = TRUE;
    return (full_state);
}
