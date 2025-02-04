#include "../includes/philo.h"

void destroy_mutexes(t_mutex *mutex, int nbr_philo, int stage)
{
    int i;

    if (stage >= 2)
    {
        pthread_mutex_destroy(&mutex->print_mtx);
        if (stage >= 3)
        {
            pthread_mutex_destroy(&mutex->time_ate_mtx);
            if (stage >= 4)
            {
                pthread_mutex_destroy(&mutex->philos_full_mtx);
                if (stage == 5)
                    pthread_mutex_destroy(&mutex->sim_status_mtx);
            }
        }
    }
    i = -1;
    while (++i < nbr_philo)
        pthread_mutex_destroy(&mutex->fork_mtx[i]);
    free(mutex->fork_mtx);
}

short stop_simulation(t_philo *philo, int stop)
{
    short status;

    pthread_mutex_lock(&philo->data->mutex.sim_status_mtx);
    if (stop)
        philo->data->sim_state.end_sim = TRUE;
    status = philo->data->sim_state.end_sim;
    pthread_mutex_unlock(&philo->data->mutex.sim_status_mtx);
    return (status);
}