



# include "philosophers.h"


static int	check_params(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_count_max = ft_atoi(argv[5]);
	else
		env->eat_count_max = 0;
	if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->eat_count_max < 0)
		return (0);
	return (1);
}




int	main(int argc, char *argv[])
{
	t_env	env;

	env.max_ate = 0;
	env.stop_condition = 0;
	if (argc < 5 || argc > 6)
		return (error_msg(ERR_USAGE));
	if (!check_params(&env, argc, argv))
		return (error_msg("Incorrect parameters.\n"));
	if (!ft_init(&env))
		return (error_msg("init error.\n"));
	if (!start_threads(&env))
		return (error_msg("threads error.\n"));
	return (0);
}