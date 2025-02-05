#include "../includes/philo_bonus.h"

static void free_data(t_data *data, int stage);
static void free_semaphores(t_semaphores *semaphores);

void error_exit(char *message, t_data *data, int stage)
{
    print_error(message);
    free_data(data, stage);
    exit(EXIT_FAILURE);
}

static void free_data(t_data *data, int stage)
{
    if (!data)
        return;
    if (stage >= 2)
    {
        if (data->config)
            free(data->config);
        if (stage >= 3)
        {
            if (data->monitor)
                free(data->monitor);
            if (stage >= 4)
            {
                if (data->semaphores)
                    free_semaphores(data->semaphores);
            }
        }
    }
    free(data);
}

static void free_semaphores(t_semaphores *semaphores)
{
    if (!semaphores)
        return;
    if (semaphores->forks)
        sem_close(semaphores->forks);
    if (semaphores->table)
        sem_close(semaphores->table);
    if (semaphores->print)
        sem_close(semaphores->print);
    if (semaphores->death)
        sem_close(semaphores->death);
    if (semaphores->full)
        sem_close(semaphores->full);
    if (semaphores->stop)
        sem_close(semaphores->stop);
    if (semaphores->sem_state)
        sem_close(semaphores->sem_state);
    free(semaphores);
}
