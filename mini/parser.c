/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:44 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:52:31 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexis(void)
{
	int	valid;

	valid = 0;
	valid += check_quote_pipe(-1, 0, 0, 0);
	valid += check_dollar(-1);
	return (valid);
}

int	parser(void)
{
	char	**mas;
	int		i;
	int		valid;

	i = -1;
	valid = lexis();
	if (valid)
	{
		printf("ERROR!!\n");
		return (1);
	}
	mas = split_parser(g_sh->str);
	while (mas[++i] != 0)
	{
		ft_lstadd_back(&g_sh->first_list, ft_lstnew(ft_strdup(mas[i])));
		if (mas[i])
			free(mas[i]);
	}
	if (mas)
		free(mas);
	if (!(ft_strcmp(g_sh->first_list->line, "|")) || \
	!(ft_strcmp(ft_lstlast(g_sh->first_list)->line, "|")))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!(ft_strcmp(ft_lstlast(g_sh->first_list)->line, "<")) || \
	!(ft_strcmp(ft_lstlast(g_sh->first_list)->line, "<<")) || \
	!(ft_strcmp(ft_lstlast(g_sh->first_list)->line, ">")) || \
	!(ft_strcmp(ft_lstlast(g_sh->first_list)->line, ">>")))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
