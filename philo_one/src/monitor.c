#include "philo_one.h"

static int	check_count(t_globals *globals, t_philo *philos)
{
	int		i;
	int		nb_eats;

	i = -1;
	while (++i < globals->nb_philo)
	{
		pthread_mutex_lock(&philos[i].state);
		nb_eats = philos[i].nb_eats;
		pthread_mutex_unlock(&philos[i].state);
		if (globals->nb_must_eat < 0 || nb_eats < globals->nb_must_eat)
			return (0);
	}
	pthread_mutex_lock(&globals->state);
	globals->is_active = 0;
	pthread_mutex_unlock(&globals->state);
	return (1);
}

static int	check_dead(t_globals *globals, t_philo *philos)
{
	int			i;
	t_mseconds	last_eat;

	i = -1;
	while (++i < globals->nb_philo)
	{
		pthread_mutex_lock(&philos[i].state);
		last_eat = philos[i].t_last_eat;
		pthread_mutex_unlock(&philos[i].state);
		if (timestamp() - last_eat > globals->t_die)
		{
			pthread_mutex_lock(&globals->state);
			globals->is_active = 0;
			printf("%ju %d %s\n", (uintmax_t)timestamp(), philos[i].id, PH_DIED);
			pthread_mutex_unlock(&globals->state);
			return (1);
		}
	}
	return (0);
}

void	monitor(t_globals *globals, t_philo *philos)
{
	while (1)
	{
		usleep(50);
		if (check_count(globals, philos) || check_dead(globals, philos))
			break ;
	}
}
