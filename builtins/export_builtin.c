/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:24 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/28 22:02:24 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_export(t_vars *mini)
{
	int	i;

	i = 0;
	mini->export = malloc(sizeof(char *) * (mini->env_len + 1));
	mini->new_export = malloc(sizeof(char *) * (mini->env_len + 10));
	if (!mini->export || !mini->new_export)
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
	sorting_export(mini);
}

int	export_builtin(t_vars *mini)
{
	int	i;

	i = -1;
	if (ft_strchr(mini->input, ' '))
		export_var(mini);
	else
	{
		while (++i < mini->env_len)
		printf("declare -x %s\n", mini->export[i]);
	}
	return (0);
}

void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		export_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	sorting_export(t_vars *mini)
{
	int	i;
	int	swapped;
	int	len;

	len = export_len(mini->export);
	if (len < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < len && 
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

