# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct data_s
{
	int				num;
	pthread_mutex_t	mutex;
}	data_t;

data_t *init_data()
{
	data_t	*data;

	data = malloc(sizeof(data_t));
	if (!data)
		exit(1);
	data->num = 0;
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

void	free_data(data_t *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

void	exit_on_error(data_t *data)
{
	free(data);
	exit(1);
}

void *foo(void *arg)
{
	data_t	*data;
	int		i;

	data = (data_t *)arg;
	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&data->mutex);
		(data->num)++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

int	main()
{
	data_t		*data;
	pthread_t	t1;
	pthread_t	t2;

	data = init_data();
	if (pthread_create(&t1, NULL, foo, data))
		exit_on_error(data);
	if (pthread_create(&t2, NULL, foo, data))
		exit_on_error(data);

	if (pthread_join(t1, NULL))
		exit_on_error(data);
	if (pthread_join(t2, NULL))
		exit_on_error(data);
	printf("%d\n", data->num);

	return (0);
}
