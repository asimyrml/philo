

#include "../philosophers.h"

static void	*routine(void *params)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)params;
	env = philo->env;
	if (philo->pos % 2 && env->count > 1)
		new_sleep(env->time_to_eat / 50, env);
	while (!env->stop_condition && !env->max_ate)
	{
		philo_eat(philo);
		philo_print("is sleeping", philo, UNLOCK);
		new_sleep(env->time_to_sleep, env);
		philo_print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}

static void	exit_threads(t_env *env)
{
	int	i;

	if (env->count == 1)
		pthread_detach(env->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < env->count)
			pthread_join(env->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < env->count)
		pthread_mutex_destroy(&env->forks[i]);
	pthread_mutex_destroy(&env->meal);
	pthread_mutex_destroy(&env->writing);
	i = -1;
	while (++i < env->count)
		free(env->philos[i].pos_str);
	free(env->philos);
	free(env->forks);
}

int	start_threads(t_env *env)
{
	int	i;

	i = -1;
	env->start_time = get_time();
	while (++i < env->count)
	{
		env->philos[i].last_ate = get_time();
		if (pthread_create(&env->philos[i].thread_id,
				NULL, routine, &(env->philos[i])))
			return (0);
	}
	philo_dead(env, env->philos);
	pthread_mutex_unlock(&env->writing);
	exit_threads(env);
	return (1);
}
