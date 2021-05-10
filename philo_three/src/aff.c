#include "philo_three.h"

void	aff(t_philo *philo, const char *mes)
{
    sem_wait(philo->globals->state);
    if (philo->globals->is_active)
        printf("%ju %d %s\n", (uintmax_t)timestamp(), philo->id, mes);
    sem_post(philo->globals->state);
}

