#include "philo_three.h"

void	aff(t_philo *philo, const char *mes)
{
	t_mseconds	t_timestamp;

	t_timestamp = timestamp();
	sem_wait(philo->state);
	printf("%013ju %d %s\n",
		(uintmax_t)(t_timestamp - philo->globals->t_start),
		philo->id, mes);
	fflush(stdout);
	sem_post(philo->state);
}
