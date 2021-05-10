#include "philo_two.h"

static t_code	init_philos(t_philo **philos, t_globals *globals)
{
	int		i;

	if (!(*philos = ft_calloc(globals->nb_philo, sizeof(t_philo))))
		return (err_malloc);
	i = -1;
	while (++i < globals->nb_philo)
	{
        (*philos)[i].id = i + 1;
        (*philos)[i].globals = globals;
        (*philos)[i].t_last_eat = chrono();
		if (pthread_mutex_init(&(*philos)[i].state, NULL))
			return (err_malloc);
	}
	return (err_ok);
}

static t_code	init_params(t_globals *globals, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (err_wrong_argc);
	if (!is_atoi(argv[1]) || !is_atoi(argv[2]) ||
		!is_atoi(argv[3]) || !is_atoi(argv[4]) ||
		(argc == 6 && !is_atoi(argv[5])))
		return (err_invalid_arg);
	globals->nb_philo = ft_atoi(argv[1]);
	globals->t_die = ft_atoi(argv[2]);
	globals->t_eat = ft_atoi(argv[3]);
	globals->t_sleep = ft_atoi(argv[4]);
	globals->nb_must_eat = argc == 6 ? ft_atoi(argv[5]) : -1;
	if (pthread_mutex_init(&globals->printer, NULL))
		return (err_malloc);
	return (err_ok);
}

static t_code	init_threads(const t_globals *globals, t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < globals->nb_philo)
	{
	    philos[i].is_active = 1;
		if (pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]))
			return (err_new_thread);
		pthread_detach(philos[i].thread);
	}
	return (err_ok);
}

int main(int argc, char *argv[])
{
	t_globals	globals;
	t_philo		*philos;
	t_code		code;

	philos = NULL;
	if ((code = init_params(&globals, argc, argv)))
		return (clean_exit(&globals, philos, code));
	if ((code = init_philos(&philos, &globals)))
		return (clean_exit(&globals, philos, code));
	if ((code = init_threads(&globals, philos)))
		return (clean_exit(&globals, philos, code));
	routine(&globals, philos);
	clean_exit(&globals, philos, err_ok);
	return (0);
}
