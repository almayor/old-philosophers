#include "philo_three.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == 0 || size == 0)
		return (NULL);
	mem = malloc(size * count);
	if (mem)
		memset(mem, 0, size * count);
	return (mem);
}

int	is_atoi(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (0);
	}
	return (ft_atoi(s) > 0);
}

int	ft_atoi(const char *s)
{
	unsigned long long	ans;
	size_t				i;

	ans = 0;
	i = -1;
	while (s[++i])
		ans = ans * 10 + (s[i] - '0');
	if (ans > INT_MAX)
		return (-1);
	else
		return (ans);
}

t_mseconds	timestamp(void)
{
	struct timeval	tv;
	t_mseconds		mseconds;

	gettimeofday(&tv, NULL);
	mseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (mseconds);
}
