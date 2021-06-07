#include "philo_three.h"

static void	update_state(t_philo *philo)
{
	sem_wait(philo->state);
	++philo->nb_eats;
	philo->t_last_eat = timestamp();
	sem_post(philo->state);
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->globals->waiter);
	sem_wait(philo->globals->forks);
	sem_wait(philo->globals->forks);
	aff(philo, PH_TAKEN_FORK);
	aff(philo, PH_TAKEN_FORK);
	aff(philo, PH_EATING);
	usleep(philo->globals->t_eat * 1000);
	sem_post(philo->globals->forks);
	sem_post(philo->globals->forks);
	sem_post(philo->globals->waiter);
	update_state(philo);
}

static void	sleeping(t_philo *philo)
{
	aff(philo, PH_SLEEPING);
	usleep(philo->globals->t_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	aff(philo, PH_THINKING);
}

_Noreturn void	routine(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, &introspect, philo))
		exit(1);
	pthread_detach(thread);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}
