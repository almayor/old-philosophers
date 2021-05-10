#include "philo_two.h"

void	aff(t_philo *philo, const char *mes)
{
    pthread_mutex_lock(&philo->globals->printer);
    printf("%ju %d %s\n", (uintmax_t)chrono(), philo->id, mes);
    pthread_mutex_unlock(&philo->globals->printer);
}

