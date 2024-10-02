/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/02 16:44:37 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(t_vars *mini, char *var)
{
	int i;

	i = 0;
	printf("var= %s\n", var);
	if (!var || !mini || !mini->export || !mini->env)
		return (NULL);
	while (i < mini->exp_len)
	{
		if (!mini->export[i])
		{
			i++;
			continue;
		}
		if (ft_strncmp(mini->export[i], var, ft_strlen(var)) == 0 &&
		mini->export[i][ft_strlen(var)] == '=')
		{
			printf("mini = %s\n", mini->export[i]);
			return (mini->export[i]);
		}
		i++;
	}
	return (NULL);
}

int	unset_builtin(t_vars *mini)
{
	char	**split;
	char 	*str;
	int		i;
	
	i = 1;
	if (ft_strncmp(mini->input, "unset\0", ft_strlen(mini->input)) == 0)
		return (1);
	split = ft_split(mini->input, ' ');
	if (!split || !split[i])
	{
		printf("No variable to unset.\n");
		return (1);
	}
	while (split[i])
	{
		str = get_var(mini, split[i]);
		printf("stringg = %s\n", str);
		if (!str)
		{
			printf("Variable not found.\n");
			return (1);
		}
		env_update(mini, str);
		exp_update(mini, str);
		i++;
	}
	return (0);
}
