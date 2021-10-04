/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:06:08 by rroland           #+#    #+#             */
/*   Updated: 2021/09/27 19:20:12 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_line_signal(int sig)
{
	// (void)sig;
	write(1, "Minishell >>   ", 15);
	write(1, " \b\b \b\nMinishell >> ", 19);
}

void	ignor_signal(int sig)
{
	// (void)sig;
	write(1, " \b\b \b\bMinishell >>   \b\b \b", 25);
}

void	signal_processing(void)
{
	signal(SIGQUIT, ignor_signal);
	signal(SIGINT, new_line_signal);
}
