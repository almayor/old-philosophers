#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <sys/wait.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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
    err_term_proc,
    err_new_proc,
    err_new_sem,
}				t_code;

# define PH_THINKING		"is thinking"
# define PH_SLEEPING		"is sleeping"
# define PH_EATING		    "is eating"
# define PH_TAKEN_FORK	    "has taken a fork"
# define PH_DIED			"died"

typedef struct	s_philo t_philo;

typedef struct	s_globals
{
    int				nb_philo;
    int				nb_must_eat;
    t_mseconds		t_eat;
    t_mseconds		t_sleep;
    t_mseconds		t_die;
    sem_t           *procs;
    sem_t           *eats;
    sem_t	        *forks;
    sem_t           *waiter;
    t_philo         *philos;
}				t_globals;

typedef struct	s_philo
{
    int				id;
    int             nb_eats;
    t_mseconds      t_last_eat;
    pid_t	        pid;
    sem_t	        *state;
    t_globals       *globals;
}				t_philo;

void            routine(t_philo *philo);

void            monitor(t_globals *globals, t_philo *philos);
t_mseconds      timestamp(void);
void            aff(t_philo *philo, const char *mes);
int             clean_exit(t_globals *globals, t_philo *philos, t_code code);
t_code          init_sems(t_globals *globals, t_philo *philos);

void            *ft_calloc(size_t count, size_t size);
int             ft_atoi(const char *s);
int             is_atoi(const char *s);
void            smart_sleep(t_philo *philo, t_mseconds duration);

#endif
