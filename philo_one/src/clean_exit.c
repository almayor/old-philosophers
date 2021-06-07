#include "philo_one.h"

static void	print_message(t_code code)
{
	if (code == err_invalid_arg)
		write(2, "Invalid arguments\n", 18);
	else if (code == err_malloc)
		write(2, "Error allocating memory\n", 24);
	else if (code == err_new_thread)
		write(2, "Error creating a thread\n", 24);
	else if (code == err_wrong_argc)
	{
		write(2, "Usage: ./philo_one number_of_philosophers", 41);
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
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(&philos[i].state);
	}
	free(philos);
}

static void	clean_forks(t_globals *globals)
{
	int	i;

	i = -1;
	while (++i < globals->nb_philo)
	{
		pthread_mutex_destroy(&globals->forks[i]);
	}
	free(globals->forks);
}

int	clean_exit(t_globals *globals, t_philo *philos, t_code code)
{
	clean_philosophers(globals, philos);
	clean_forks(globals);
	print_message(code);
	pthread_mutex_destroy(&globals->state);
	return (code != err_ok);
}
