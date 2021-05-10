#include "philo_three.h"

static void print_message(t_code code)
{
    if (code == err_invalid_arg)
        write(2, "Invalid arguments\n", 18);
    else if (code == err_malloc)
        write(2, "Error allocating memory\n", 24);
    else if (code == err_new_proc)
        write(2, "Error creating a process\n", 25);
    else if (code == err_new_sem)
        write(2, "Error creating a semaphore\n", 27);
    else if (code == err_wrong_argc)
    {
        write(2, "Usage: ./philo_three number_of_philosophers", 41);
        write(2, " time_to_die time_to_eat time_to_sleep", 38);
        write(2, " [number_of_times_each_philosopher_must_eat]\n", 45);
    }
}

static void clean_philosophers(t_globals *globals, t_philo *philos)
{
    t_code  code;
    int     i;
    int     status;

    if (!philos)
        return (err_ok);
    code = err_ok;
    i = -1;
    while (++i < globals->nb_philo)
    {
        kill(philos[i].pid, SIGTERM);
        if (philos[i].state)
            sem_close(philos[i].state);
    }
    free(philos);
}

int	clean_exit(t_globals *globals, t_philo *philos, t_code code)
{
    clean_philosophers(globals, philos);
    print_message(code);
    if (globals->procs)
        sem_close(globals->procs);
    if (globals->forks)
        sem_close(globals->forks);
    if (globals->waiter)
        sem_close(globals->waiter);
    return (code == err_ok ? 0 : 1);
}
