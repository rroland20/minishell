/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:08:52 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:36:51 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_list *list)
{
	t_list	*find_pipe;
	int		count;

	count = 0;
	find_pipe = list;
	while (find_pipe)
	{
		if (find_pipe->line[0] == '|')
			count++;
		find_pipe = find_pipe->next;
	}
	return (count);
}

int	**init_pipe(int count)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (count + 1));
	if (!pipes)
		exit(10);
	while (i != count)
	{
		pipes[i] = malloc(sizeof(int ) * 2);
		if (!pipes[i])
			exit(10);
		pipe(pipes[i]);
		i++;
	}
	pipes[i] = 0;
	if (count)
		return (pipes);
	return (0);
}

int	check_redirect(char *line)
{
	if (!ft_strcmp(line, "<<") || !ft_strcmp(line, ">>") \
			|| !ft_strcmp(line, "<") || !ft_strcmp(line, ">"))
		return (1);
	return (0);
}

int	redirect(t_list *list)
{
	int	fd;

	if (!list->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (list->next->line[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!ft_strcmp(list->line, "<<") || !ft_strcmp(list->line, ">>"))
		fd = open(list->next->line, O_WRONLY | O_CREAT);
	else
		fd = open(list->next->line, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (!ft_strcmp(list->line, "<<") || !ft_strcmp(list->line, "<"))
		dup2(fd, 0);
	else
		dup2(fd, 1);
	return (0);
}

void	close_pipes(t_cmd *command)
{
	int	i;

	i = 0;
	while (i != command->count_pipes)
	{
		close(command->pipes[i][0]);
		close(command->pipes[i][1]);
		i++;
	}
}
