#include "philo_one.h"

void	aff(t_philo *philo, const char *mes)
{
	pthread_mutex_lock(&philo->globals->state);
	if (philo->globals->is_active)
		printf("%013ju %d %s\n",
			(uintmax_t)(timestamp() - philo->globals->t_start),
			philo->id, mes);
	pthread_mutex_unlock(&philo->globals->state);
}
