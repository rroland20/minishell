/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:00:12 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 21:09:53 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_list **first_list)
{
	t_list	*tmp;

	tmp = *first_list;
	*first_list = (*first_list)->next;
	if (tmp->line)
		free(tmp->line);
	if (tmp)
		free(tmp);
}

void	free_full_lst(t_list **first_list)
{
	while (*first_list)
		free_lst(first_list);
}

void	clear_all(void)
{
	if (g_sh->str)
		free(g_sh->str);
	free_full_lst(&g_sh->first_list);
}
