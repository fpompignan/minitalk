/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:09:45 by fassier-          #+#    #+#             */
/*   Updated: 2022/02/17 16:10:23 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar('0' + nb);
}

void	affichage_message(int *i, char sentence[1000], int *j)
{
	*i = 0;
	while (sentence[*i] != 0)
		ft_putchar(sentence[(*i)++]);
	ft_putchar(sentence[*i]);
	*i = 0;
	*j = 0;
	ft_putchar('\n');
}

void	handler(int signum)
{
	static int	buf[8];
	static char	sentence[1000];
	static int	i;
	static int	j;
	int			nb;

	nb = 1;
	if (signum == SIGUSR1)
		buf[i++] = 1;
	if (signum == SIGUSR2)
		buf[i++] = 0;
	if (i == 8)
	{
		i = 0;
		nb = 0;
		while (i <= 7)
			nb = (2 * nb) + buf[i++];
		sentence[j] = nb;
		j++;
		i = 0;
	}
	if (nb == 0)
		affichage_message(&i, sentence, &j);
}

int	main(void)
{
	struct sigaction	s;	

	ft_putnbr(getpid());
	ft_putchar('\n');
	s.sa_handler = handler;
	s.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
