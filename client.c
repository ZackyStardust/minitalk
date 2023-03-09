/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:24:43 by fpereira          #+#    #+#             */
/*   Updated: 2023/02/22 16:27:13 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	error(char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("client: unexpected error.\n", 2);
	exit(EXIT_FAILURE);
}

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(str);
		return (0);
	}
	return (1);
}

int	send_bit(int pid, char *str)
{
	static char				*msg = 0;
	static int				saved_pid = 0;
	static unsigned long	bits = -1;

	if (str)
		msg = ft_strdup(str);
	if (!msg)
		error(0);
	if (pid)
		saved_pid = pid;
	if ((++bits / 8) < ft_strlen(msg) && msg[bits / 8])
	{
		if (msg[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(saved_pid, SIGUSR2) == -1)
				error(msg);
		}
		else if (kill(saved_pid, SIGUSR1) == -1)
			error(msg);
		return (0);
	}
	if (!send_null(saved_pid, msg))
		return (0);
	free(msg);
	return (1);
}

void	handler_sigusr(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_bit(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("client: server ended unexpectdly.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_putstr_fd("client: operation successful.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || ft_str_isnumeric(argv[1]))
	{
		ft_putstr_fd("client: invalid arguments.\n", 2);
		ft_putstr_fd("correct format: [./client <PID> <STR>].\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	send_bit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
