/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:19:40 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 21:20:17 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exita(unsigned char num)
{
	clear_all();
	free_full_lst(&g_sh->env);
	exit(num);
}

void	exit_cmd(void)
{
	int	argc;
	int	res;

	argc = ft_lstsize(g_sh->first_list);
	if (argc == 1)
	{
		write(1, "exit\n", 5);
		exita(0);
	}
	else if (argc == 2)
	{
		write(1, "exit\n", 5);
		res = ft_atoi(g_sh->first_list->next->line);
		if (res == -1)
		{
			if (!ft_strcmp(g_sh->first_list->next->line, "?"))
				exita(1);
			printf("minishell: exit: %s: numeric argument required\n", \
			g_sh->first_list->next->line);
		}
		else
			exita((unsigned char)res);
	}
	else
	{
		res = ft_atoi(g_sh->first_list->next->line);
		if (res == -1)
			printf("minishell: exit: %s: numeric argument required\n", \
			g_sh->first_list->next->line);
		else
			printf("exit\nminishell: exit: too many arguments\n");
	}
}
