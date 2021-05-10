#include "philo_two.h"

static void	update_state(t_philo *philo)
{
    pthread_mutex_lock(&philo->state);
    ++philo->nb_eats;
    philo->t_last_eat = chrono();
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->state);
}

static void	eating(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    aff(philo, PH_TAKEN_FORK);
    pthread_mutex_lock(philo->rfork);
    aff(philo, PH_TAKEN_FORK);
    aff(philo, PH_EATING);
    pthread_mutex_lock(&philo->state);
    philo->is_eating = 1;
    pthread_mutex_unlock(&philo->state);
    usleep(philo->globals->t_eat * 1000);
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    update_state(philo);
}

static void sleeping(t_philo *philo)
{
    aff(philo, PH_SLEEPING);
    usleep(philo->globals->t_sleep * 1000);
}

static int active(t_philo *philo)
{
    int is_active;

    pthread_mutex_lock(&philo->state);
    is_active = philo->is_active;
    pthread_mutex_unlock(&philo->state);
    return is_active;
}

void *philosopher(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (active(philo)) {
        eating(philo);
        sleeping(philo);
        aff(philo, PH_THINKING);
    }
    return (NULL);
}


