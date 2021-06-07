#include "philo_three.h"

static void	check_eats(t_philo *philo)
{
	static int	signalled = 0;
	int			nb_eats;

	if (signalled)
		return ;
	sem_wait(philo->state);
	nb_eats = philo->nb_eats;
	sem_post(philo->state);
	if (philo->globals->nb_must_eat > 0
		&& nb_eats > philo->globals->nb_must_eat)
	{
		sem_post(philo->globals->eats);
		signalled = 1;
	}
}

static void	check_dead(t_philo *philo)
{
	t_mseconds	last_eat;

	sem_wait(philo->state);
	last_eat = philo->t_last_eat;
	if (timestamp() - last_eat > philo->globals->t_die)
	{
		printf("%ju %d %s\n", (uintmax_t)timestamp(), philo->id, PH_DIED);
		sem_post(philo->globals->finish);
		exit(0);
	}
	sem_post(philo->state);
}

_Noreturn void	*introspect(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		check_eats(philo);
		check_dead(philo);
		usleep(50);
	}
}
