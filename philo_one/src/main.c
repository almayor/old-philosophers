#include "philo_one.h"

static void	assign_forks(t_philo *philos, const t_globals *globals)
{
	int		i;

	i = -1;
	while (++i < globals->nb_philo)
	{
		if (i == 0)
		{
			philos[i].lfork = &globals->forks[0];
			philos[i].rfork = &globals->forks[globals->nb_philo - 1];
		}
		else
		{
			philos[i].lfork = &globals->forks[i - 1];
			philos[i].rfork = &globals->forks[i];
		}
	}
}

static t_code	init_philos(t_philo **philos, t_globals *globals)
{
	int		i;

	*philos = ft_calloc(globals->nb_philo, sizeof(t_philo));
	if (!philos)
		return (err_malloc);
	globals->forks = ft_calloc(globals->nb_philo, sizeof(pthread_mutex_t));
	if (!globals->forks)
		return (err_malloc);
	i = -1;
	while (++i < globals->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].globals = globals;
		(*philos)[i].t_last_eat = timestamp();
		if (pthread_mutex_init(&(*philos)[i].state, NULL)
			|| pthread_mutex_init(&globals->forks[i], NULL))
			return (err_malloc);
	}
	assign_forks(*philos, globals);
	return (err_ok);
}

static t_code	init_params(t_globals *globals, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (err_wrong_argc);
	if (!is_atoi(argv[1]) || !is_atoi(argv[2])
		|| !is_atoi(argv[3]) || !is_atoi(argv[4])
		|| (argc == 6 && is_atoi(argv[5]) < 0))
		return (err_invalid_arg);
	globals->is_active = 1;
	globals->nb_philo = ft_atoi(argv[1]);
	globals->t_die = ft_atoi(argv[2]);
	globals->t_eat = ft_atoi(argv[3]);
	globals->t_sleep = ft_atoi(argv[4]);
	globals->t_start = timestamp();
	if (argc == 6)
		globals->nb_must_eat = ft_atoi(argv[5]);
	else
		globals->nb_must_eat = -1;
	if (pthread_mutex_init(&globals->state, NULL))
		return (err_malloc);
	return (err_ok);
}

static t_code	init_threads(const t_globals *globals, t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < globals->nb_philo)
	{
		usleep(100);
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			return (err_new_thread);
	}
	return (err_ok);
}

int	main(int argc, char *argv[])
{
	t_globals	globals;
	t_philo		*philos;
	t_code		code;

	memset(&globals, 0, sizeof(t_globals));
	philos = NULL;
	code = init_params(&globals, argc, argv);
	if (code)
		return (clean_exit(&globals, philos, code));
	code = init_philos(&philos, &globals);
	if (code)
		return (clean_exit(&globals, philos, code));
	code = init_threads(&globals, philos);
	if (code)
		return (clean_exit(&globals, philos, code));
	monitor(&globals, philos);
	clean_exit(&globals, philos, err_ok);
	return (0);
}
