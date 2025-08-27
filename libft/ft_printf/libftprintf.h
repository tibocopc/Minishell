/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaiache <aaiache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:50:32 by aaiache           #+#    #+#             */
/*   Updated: 2025/05/12 11:41:58 by aaiache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printchar(char c);
int	ft_printf(const char *format, ...);
int	ft_printhexa(const unsigned int n, char c);
int	ft_printnbr(int nb);
int	ft_printptr(unsigned long long int ptr);
int	ft_printstr(const char *str);
int	ft_printunbr(const unsigned int nb);

#endif
