#include "minishell.h"

char	**list_to_array(t_list *list)
{
	char	**env;
	t_list	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list)
	{
		env[i] = ft_strdup(list->line);
		list = list->next;
		i++;
	}
	env[i] = 0;
	return (env);
}

void	wait_pids(t_cmd *command)
{
	int	i;

	i = 0;
	while (i <= command->count_pipes)
	{
		waitpid(command->pids[i], 0, 0);
		i++;
	}
}
