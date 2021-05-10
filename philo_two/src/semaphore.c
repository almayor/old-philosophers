#include "philo_two.h"

static sem_t    *create_sem(const char *name, int val)
{
    sem_t   *sem;

    sem = sem_open(name, O_CREAT | O_EXCL, 0644, val);
    if (sem != SEM_FAILED && sem_unlink(name))
    {
        sem_close(sem);
        return (SEM_FAILED);
    }
    return sem;
}


static const char *get_name(void)
{
    static char name[] = "ph_sem_0000";
    static int  counter = 1;
    int         c;
    int         idx;

    if (counter > 9999)
        return (NULL);
    c = counter++;
    idx = 11;
    while (--idx >= 7)
    {
        name[idx] = (c % 10) + '0';
        c /= 10;
    }
    return (name);
}

static t_code  init_sems_global(t_globals *globals)
{
    globals->state = create_sem("sem_global_state", 1);
    globals->forks = create_sem("sem_forks", globals->nb_philo);
    globals->waiter = create_sem("sem_waiter", globals->nb_philo - 1);
    if (globals->state == SEM_FAILED ||
        globals->forks == SEM_FAILED ||
        globals->waiter == SEM_FAILED)
        return (err_new_sem);
    return (err_ok);
}

static t_code   init_sems_philo(t_globals *globals, t_philo *philos)
{
    int		    i;
    const char  *name;

    i = -1;
    while (++i < globals->nb_philo)
    {
        name = get_name();
        philos[i].state = create_sem(name, 1);
        if (philos[i].state == SEM_FAILED)
            return (err_new_sem);
    }
    return (err_ok);
}

t_code  init_sems(t_globals *globals, t_philo *philos)
{
    t_code  code;

    if ((code = init_sems_global(globals)) ||
        (code = init_sems_philo(globals, philos)))
        return (code);
    return (err_ok);
}

