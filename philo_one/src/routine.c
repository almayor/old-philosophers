#include "philo_one.h"

static void	update_state(t_philo *philo)
{
    pthread_mutex_lock(&philo->state);
    ++philo->nb_eats;
    philo->t_last_eat = timestamp();
    pthread_mutex_unlock(&philo->state);
}

static void	eating(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    aff(philo, PH_TAKEN_FORK);
    pthread_mutex_lock(philo->rfork);
    aff(philo, PH_TAKEN_FORK);
    aff(philo, PH_EATING);
    update_state(philo);
    smart_sleep(philo, philo->globals->t_eat);
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
}

static void sleeping(t_philo *philo)
{
    aff(philo, PH_SLEEPING);
    smart_sleep(philo, philo->globals->t_sleep);
}

static void thinking(t_philo *philo)
{
    aff(philo, PH_THINKING);
}

void *routine(void *arg)
{
    t_philo *philo;
    int     is_active;

    philo = (t_philo *)arg;
    is_active = 1;
    while (is_active) {
        eating(philo);
        sleeping(philo);
        thinking(philo);
        pthread_mutex_lock(&philo->globals->state);
        is_active = philo->globals->is_active;
        pthread_mutex_unlock(&philo->globals->state);
    }
    return (NULL);
}


