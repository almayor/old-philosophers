#include "philo_three.h"

static t_code	init_philos(t_philo **philos, t_globals *globals)
{
	int		    i;

	if (!(*philos = ft_calloc(globals->nb_philo, sizeof(t_philo))))
		return (err_malloc);
	i = -1;
	while (++i < globals->nb_philo)
	{
        (*philos)[i].id = i + 1;
        (*philos)[i].globals = globals;
        (*philos)[i].t_last_eat = timestamp();
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
	return (err_ok);
}

static t_code	init_procs(const t_globals *globals, t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < globals->nb_philo)
	{
	    usleep(100);
        philos[i].pid = fork();
		if (philos[i].pid < 0)
			return (err_new_proc);
		if (philos[i].pid == 0)
        {
		    routine(&philos[i]);
		    exit(0);
        }
	}
	return (err_ok);
}

int main(int argc, char *argv[])
{
	t_globals	globals;
	t_philo		*philos;
	t_code		code;

	memset(&globals, 0, sizeof(t_globals));
	philos = NULL;
	if ((code = init_params(&globals, argc, argv)) ||
	    (code = init_philos(&philos, &globals)) ||
	    (code = init_sems(&globals, philos)) ||
	    (code = init_procs(&globals, philos)))
		return (clean_exit(&globals, philos, code));
	sem_wait(globals.procs);
	clean_exit(&globals, philos, err_ok);
	return (0);
}
