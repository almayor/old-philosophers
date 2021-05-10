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
    smart_sleep(philo, philo->globals->t_eat);
    sem_post(philo->globals->forks);
    sem_post(philo->globals->forks);
    sem_post(philo->globals->waiter);
    update_state(philo);
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

void routine(t_philo *philo)
{

    while (1) {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
}


