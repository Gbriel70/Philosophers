#include "../includes/philo_bonus.h"

void kill_all_philos(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->config->nbr_philos)
	{
		kill(data->philo_pid[i], SIGKILL);
	}
}

void wait_finish_philos(t_data *data)
{
	int status;

	while (waitpid(-1, &status, 0) != -1)
		;
	close_shared_semaphores(data);
	unlink_shared_semaphores();
	free(data->philo_pid);
}

short simulation_stopped(t_data *data, int stop)
{
	short state;

	sem_wait(data->semaphores->stop);
	if (stop)
		data->monitor->sim_stop = TRUE;
	state = data->monitor->sim_stop;
	sem_post(data->semaphores->stop);
	return (state);
}

void close_shared_semaphores(t_data *data)
{
	sem_close(data->semaphores->forks);
	sem_close(data->semaphores->table);
	sem_close(data->semaphores->print);
	sem_close(data->semaphores->death);
	sem_close(data->semaphores->full);
	sem_close(data->semaphores->stop);
}

void unlink_shared_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/table");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/full");
	sem_unlink("/stop");
}
void cleanup(t_data *data)
{
	close_shared_semaphores(data);
	unlink_shared_semaphores();

    free(data->semaphores);
    free(data->monitor);
    free(data->config);
}