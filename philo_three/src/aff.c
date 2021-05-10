#include "philo_three.h"

void	aff(t_philo *philo, const char *mes)
{
    sem_wait(philo->state);
    printf("%ju %d %s\n", (uintmax_t)timestamp(), philo->id, mes);
    fflush(stdout);
    sem_post(philo->state);
}

