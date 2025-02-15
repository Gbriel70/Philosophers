#include "../includes/philo_bonus.h"

char *ft_utoa(int i)
{
	int len;
	char *str;
	long nbr;

	nbr = i;
	len = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (i == 0)
		str[0] = '0';
	nbr = i;
	while (nbr > 0)
	{
		str[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

char *ft_strjoin(char *str, char *str2)
{
	char *new_str;
	int i;
	int j;

	if (!str || !str2)
		return (NULL);
	new_str = malloc(sizeof(char) * (strlen(str) + strlen(str2) + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	j = -1;
	while (str2[++j])
		new_str[i + j] = str2[j];
	new_str[i + j] = '\0';
	return (new_str);
}

pid_t ft_fork(t_data *data)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		close_shared_semaphores(data);
		unlink_shared_semaphores();
		free(data->philo_pid);
		free(data->config);
		free(data->monitor);
		free(data->semaphores);
		free(data);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
