#include "../includes/philo_bonus.h"

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