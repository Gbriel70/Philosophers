#include "../includes/philo_bonus.h"

static void get_unique_name(t_philo *philo, char *name)
{
	char *semaphore_name;
	char *id_str;

	ft_utoa(philo->id);
	semaphore_name = ft_strjoin(name, id_str);
	free(id_str);
	return (semaphore_name);
}

static void init_philo(t_philo *philo, t_data *data,  int i)
{
	philo->id = i + 1;
	philo->time_last_ate = calc_elapsed_ms(philo->data->monitor->start_time);
	philo->times_eaten = 0;
	philo->sem_state_name = get_unique_name(philo, "state");
	philo->data = data;
	sem_unlink(philo->sem_state_name);
	philo->sem_state_name = sem_open(philo->sem_state_name, O_CREAT, 0660, 1);
}

void philo_rouitine(t_data **data, int i)
{
	t_philo *philo;

	init_philo(&philo, data,  i);
}