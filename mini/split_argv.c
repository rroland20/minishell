/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:09:05 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 21:41:31 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		++i;
	}
	free(ar);
}

static void	count_word(t_list *list, int *count)
{
	*count = 0;
	while (list)
	{
		if (list->line[0] == '|')
			break ;
		if (check_redirect(list->line))
		{
			while (list && check_redirect(list->line))
			{
				list = list->next;
				if (list)
					list = list->next;
			}
		}
		else if (list && list->line[0] != '|')
		{
			*count += 1;
			list = list->next;
		}
	}
}

static void	loop_command(t_list **list, char **argv, int *i)
{
	while (*list)
	{
		if ((*list)->line[0] == '|')
			break ;
		while (*list && check_redirect((*list)->line))
		{
			if (redirect(*list))
				break ;
			*list = (*list)->next;
			if (*list)
				*list = (*list)->next;
		}
		if (*list && (*list)->line[0] != '|')
		{
			argv[*i] = ft_strdup((*list)->line);
			*list = (*list)->next;
			*i += 1;
		}
	}
}

char	**split_argv(t_list **list)
{
	char	**argv;
	int		count;
	t_list	*first;
	int		i;

	i = 0;
	first = *list;
	if (*list == 0)
		return (0);
	count_word(first, &count);
	if (count == 0)
		return (0);
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (0);
	loop_command(list, argv, &i);
	argv[i] = 0;
	return (argv);
}
