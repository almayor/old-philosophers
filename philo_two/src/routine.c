#include "philo_two.h"

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
    update_state(philo);
    smart_sleep(philo, philo->globals->t_eat);
    sem_post(philo->globals->forks);
    sem_post(philo->globals->forks);
    sem_post(philo->globals->waiter);
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
        sem_wait(philo->globals->state);
        is_active = philo->globals->is_active;
        sem_post(philo->globals->state);
    }
    return (NULL);
}


