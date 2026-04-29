/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:45:24 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/29 16:57:17 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	if (*str == '+')
		str++;
	while (ft_is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int	ft_is_valid_integer(const char *str)
{
	if (*str == '+')
		str++;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_putstr_err(const char *message)
{
	write(2, message, strlen(message));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
