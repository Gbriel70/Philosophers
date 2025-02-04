#include "../includes/philo.h"

static int init_config(t_config *config, int ac, char **av);
static int init_mutexes(t_mutex *mutex, int nbr_philo);
static int init_sim_state(t_sim_state *sim_state);

t_data *init(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Falha ao alocar t_data"), NULL);
	if (init_config(&data->config, ac, av) != 0)
	{
		free(data);
		return (print_error("Falha ao inicializar config"), NULL);
	}
	if (init_mutexes(&data->mutex, data->config.nbr_philo) != 0)
	{
		free(data);
		return (print_error("Falha ao inicializar mutexes"), NULL);
	}
	if (init_sim_state(&data->sim_state) != 0)
	{
		destroy_mutexes(&data->mutex, data->config.nbr_philo, 0);
		free(data);
		return (print_error("Falha ao inicializar sim_state"), NULL);
	}
	return (data);
}

static int init_config(t_config *config, int ac, char **av)
{
	config->nbr_philo = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		config->nbr_must_eat = ft_atoi(av[5]);
	else
		config->nbr_must_eat = -1;
	return (0);
}

static int init_mutexes(t_mutex *mutex, int nbr_philo)
{
	int i;

	mutex->fork_mtx = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!mutex->fork_mtx)
		return (print_error("Falha ao alocar mutex dos forks"));
	i = -1;
	while(++i < nbr_philo)
	{
		if (pthread_mutex_init(&mutex->fork_mtx[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&mutex->fork_mtx[i]);
			return (print_error("Falha ao inicializar mutex do fork"));
		}
	}
	if (pthread_mutex_init(&mutex->print_mtx, NULL) != 0)
		destroy_mutexes(mutex, nbr_philo, 1);
	if (pthread_mutex_init(&mutex->time_ate_mtx, NULL) != 0)
		destroy_mutexes(mutex, nbr_philo, 2);
	if (pthread_mutex_init(&mutex->philos_full_mtx, NULL) != 0)
		destroy_mutexes(mutex, nbr_philo, 3);
	if (pthread_mutex_init(&mutex->sim_status_mtx, NULL) != 0)
		destroy_mutexes(mutex, nbr_philo, 4);
	return (0);
}

static int init_sim_state(t_sim_state *sim_state)
{

	sim_state->start_time = get_current_time_ms();
	sim_state->end_sim = FALSE;
	return (0);
}
