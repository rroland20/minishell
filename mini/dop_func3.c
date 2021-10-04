/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:43:28 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:07:38 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*a;

	a = lst;
	if (a == NULL)
		return (0);
	while (a->next != NULL)
		a = a->next;
	return (a);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list) + 1);
	if (!new)
		return (0);
	new->line = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int		a;
	t_list	*b;

	b = lst;
	a = 0;
	if (b == NULL)
		return (0);
	while (b->next != NULL)
	{
		a++;
		b = b->next;
	}
	a++;
	return (a);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst1;

	lst1 = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		lst1 = ft_lstlast(*lst);
		lst1->next = new;
	}
}
