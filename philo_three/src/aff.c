#include "philo_three.h"

void	aff(t_philo *philo, const char *mes)
{
	sem_wait(philo->state);
	printf("%013ju %d %s\n",
		(uintmax_t)(timestamp() - philo->globals->t_start),
		philo->id, mes);
	fflush(stdout);
	sem_post(philo->state);
}
