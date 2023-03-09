/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:13:47 by fpereira          #+#    #+#             */
/*   Updated: 2023/01/30 10:14:41 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

char	*ft_strdup(const char *src);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_str_isnumeric(char *str);
void	ft_putnbr_fd(int n, int fd);
char	*ft_straddc_first(char c);
char	*ft_straddc(char *str, char c);
size_t	ft_strlen(const char *str);

#endif