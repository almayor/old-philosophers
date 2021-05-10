#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef uintmax_t	t_mseconds;

typedef enum	e_code
{
    err_ok,
    err_wrong_argc,
    err_invalid_arg,
    err_malloc,
    err_new_thread
}				t_code;

# define PH_THINKING		"is thinking"
# define PH_SLEEPING		"is sleeping"
# define PH_EATING		    "is eating"
# define PH_TAKEN_FORK	    "has taken a fork"
# define PH_DIED			"died"

typedef struct	s_globals
{
    int				nb_philo;
    int				nb_must_eat;
    int             is_active;
    t_mseconds		t_eat;
    t_mseconds		t_sleep;
    t_mseconds		t_die;
    pthread_mutex_t	state;
    pthread_mutex_t	*forks;
}				t_globals;

typedef struct	s_philo
{
    int				id;
    int             nb_eats;
    t_mseconds      t_last_eat;
    pthread_t	    thread;
    pthread_mutex_t	*lfork;
    pthread_mutex_t	*rfork;
    pthread_mutex_t	state;
    t_globals       *globals;
}				t_philo;

void            *routine(void *philo);

void            monitor(t_globals *globals, t_philo *philos);
t_mseconds      timestamp(void);
void            aff(t_philo *philo, const char *mes);
int             clean_exit(t_globals *globals, t_philo *philos, t_code code);

void            *ft_calloc(size_t count, size_t size);
int             ft_atoi(const char *s);
int             is_atoi(const char *s);
void            smart_sleep(t_philo *philo, t_mseconds duration);

#endif
