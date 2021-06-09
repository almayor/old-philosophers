#include "philo_two.h"

static void	print_message(t_code code)
{
	if (code == err_invalid_arg)
		write(2, "Invalid arguments\n", 18);
	else if (code == err_malloc)
		write(2, "Error allocating memory\n", 24);
	else if (code == err_new_thread)
		write(2, "Error creating a thread\n", 24);
	else if (code == err_new_sem)
		write(2, "Error creating a semaphore\n", 27);
	else if (code == err_wrong_argc)
	{
		write(2, "Usage: ./philo_two number_of_philosophers", 41);
		write(2, " time_to_die time_to_eat time_to_sleep", 38);
		write(2, " [number_of_times_each_philosopher_must_eat]\n", 45);
	}
}

static void	clean_philosophers(t_globals *globals, t_philo *philos)
{
	int	i;

	if (!philos)
		return ;
	i = -1;
	while (++i < globals->nb_philo)
	{
		sem_post(globals->forks);
		sem_post(globals->waiter);
		pthread_join(philos[i].thread, NULL);
		if (philos[i].state)
			sem_close(philos[i].state);
	}
	free(philos);
}

int	clean_exit(t_globals *globals, t_philo *philos, t_code code)
{
	clean_philosophers(globals, philos);
	print_message(code);
	if (globals->state)
		sem_close(globals->state);
	if (globals->forks)
		sem_close(globals->forks);
	if (globals->waiter)
		sem_close(globals->waiter);
	if (code == err_ok)
		return (0);
	else
		return (1);
}
