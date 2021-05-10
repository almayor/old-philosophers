#include "philo_three.h"

static void	*monitor_counts(void *arg)
{
   t_globals   *globals;
   int		    i;

   globals = (t_globals *)arg;
   sem_wait(globals->finish);
   i = -1;
   while (++i < globals->nb_philo)
       sem_wait(globals->eats);
   sem_post(globals->finish);
   return (NULL);
}

t_code monitor(t_globals *globals)
{
    pthread_t   thread;

    usleep(1000);
    if (pthread_create(&thread, NULL, &monitor_counts, globals))
       return (err_new_thread);
    usleep(1000);
    pthread_detach(thread);
    sem_wait(globals->finish);
    return (err_ok);
}

