/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:24 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/27 16:02:27 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_export(t_vars *mini)
{
	int	i;
	int j;

	i = 0;
	mini->export = malloc(sizeof(char *) * (mini->env_len + 1));
	if (!mini->export)
		return ;
	while (i < mini->env_len)
	{
		if (!mini->env[i])
		{
			i++;
			continue;
		}
		if (mini->env[i])
		{
			mini->export[i] = ft_strdup(mini->env[i]);
			i++;
		}
	}
	mini->export[i] = NULL;
	j = -1;
	while (++j < mini->env_len)
		printf("export = %s\n", mini->export[j]);
	sorting_export(mini);
}

int	export_builtin(t_vars *mini)
{
	int	i;

	i = -1;
	while (++i < mini->env_len)
		printf("declare -x %s\n", mini->export[i]);
	return (0);
}

void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sorting_export(t_vars *mini)
{
	int	i;
	int	swapped;

	if (mini->env_len < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < mini->env_len - 1 && 
		mini->export[i] && mini->export[i + 1])
		{
			if (ft_strncmp(mini->export[i], \
				mini->export[i + 1], ft_strlen(mini->export[i])) > 0)
			{
				swap_strings(&mini->export[i], &mini->export[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

