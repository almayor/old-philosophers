#include "philo_two.h"

t_mseconds	chrono(void)
{
    struct timeval	tv;
    t_mseconds		mseconds;

    gettimeofday(&tv, NULL);
    mseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (mseconds);
}

