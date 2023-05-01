/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:35:28 by fassier-          #+#    #+#             */
/*   Updated: 2022/02/17 13:23:01 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

long	ft_atoi(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = 10 * nb + (str[i] - 48);
		i++;
	}
	return (nb);
}

void	send_char(int pid, char c)
{
	int	i;
	int	ret;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 1)
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (ret)
		{
			write (1, "erreur dans l'envoi du signal\n", 30);
			exit(1);
		}
		usleep(30);
		i--;
	}
	usleep(100);
}

void	check_error(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		write(1, "error : bad number of arguments\n", 32);
		exit (1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] < '0' || argv[1][i] > '9')
		{
			write(1, "error :bad argument\n", 20);
			exit(1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) > 2147483647)
	{
		write(1, "error :bad argument\n", 20);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	check_error(argc, argv);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
