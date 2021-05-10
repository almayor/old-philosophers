#include "philo_one.h"

static int	eaten_enough(const t_globals *globals, t_philo	*philos)
{
    int		i;

    i = -1;
    while (++i < globals->nb_philo)
    {
        pthread_mutex_lock(&philos[i].state);
        if (!philos[i].is_eating && philos[i].nb_eats < globals->nb_must_eat)
        {
            pthread_mutex_unlock(&philos[i].state);
            return (0);
        }
        pthread_mutex_unlock(&philos[i].state);
    }
    return (1);
}

static void inactivate(t_globals *globals, t_philo *philos)
{
    int		i;

    i = -1;
    while (++i < globals->nb_philo)
    {
        pthread_mutex_lock(&philos[i].state);
        philos[i].is_active = 0;
        pthread_mutex_unlock(&philos[i].state);
    }
}

static t_mseconds time_since_eat(t_philo *philo)
{
    t_mseconds  time;

    pthread_mutex_lock(&philo->state);
    time = chrono() - philo->t_last_eat;
    pthread_mutex_unlock(&philo->state);
    return time;

}
void routine(t_globals *globals, t_philo *philos)
{
    int     i;

    while (1)
    {
        i = -1;
        while (++i < globals->nb_philo)
        {
            if (time_since_eat(&philos[i]) > globals->t_die)
            {
                inactivate(globals, philos);
                aff(&philos[i], PH_DIED);
                return;
            }
        }
        if (globals->nb_must_eat > 0 && eaten_enough(globals, philos))
            break;
    }
    inactivate(globals, philos);
}

