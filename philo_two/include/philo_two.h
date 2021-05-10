#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
#include <semaphore.h>

typedef uintmax_t	t_mseconds;

typedef enum	e_code
{
    err_ok,
    err_wrong_argc,
    err_invalid_arg,
    err_malloc,
    err_new_thread
}				t_code;

# define SEM_NAME           "philosophers_fork"
# define PH_THINKING		"is thinking"
# define PH_SLEEPING		"is sleeping"
# define PH_EATING		    "is eating"
# define PH_TAKEN_FORK	    "has taken a fork"
# define PH_DIED			"died"

typedef struct	s_globals
{
    int				nb_philo;
    int				nb_must_eat;
    t_mseconds		t_eat;
    t_mseconds		t_sleep;
    t_mseconds		t_die;
    pthread_mutex_t	printer;
}				t_globals;

typedef struct	s_philo
{
    int				id;
    int             is_eating;
    int             is_active;
    pthread_t	    thread;
    unsigned int	nb_eats;
    t_mseconds		t_last_eat;
    pthread_mutex_t	state;
    sem_t           *fork;
    t_globals       *globals;
}				t_philo;

void            *philosopher(void *philo);
void            routine(t_globals *globals, t_philo	*philos);
t_mseconds	    chrono(void);
void	        aff(t_philo *philo, const char *mes);
int	            clean_exit(t_globals *globals, t_philo *philos, t_code code);

void            *ft_calloc(size_t count, size_t size);
int             ft_atoi(const char *s);
int             is_atoi(const char *s);

#endif