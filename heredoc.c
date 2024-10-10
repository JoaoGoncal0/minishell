/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/10 15:53:59 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_delimiters(char **split)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			if (split[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

void	free_array(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array[i]);
}

char	**heredoc_lim_array(t_vars *mini)
{
	int		i;
	char	**split;
	char	**array;
	int		j;

	i = 0;
	j = 0;
	split = ft_split(mini->input, ' ');
	array = malloc(sizeof(char *) * (count_delimiters(split) + 1));
	if (!array)
		return (NULL);
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			i++;
			array[j] = ft_strdup(split[i]);
			if (!array[j])
			{
				free_array(array);
				free_array(split);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	array[i] = NULL;
	j = -1;
	while (++j < 3)
		printf("array = %s\n", array[j]);
	return (array);
}

// 