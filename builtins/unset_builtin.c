/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/25 14:58:26 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(t_vars *mini, char *var)
{
	int i;

	i = 0;
	if (!var || !mini || !mini->env)
		return (NULL);
	while (i < mini->env_len)
	{
		if (!mini->env[i])
		{
			i++;
			continue;
		}
			
		if (ft_strncmp(mini->env[i], var, ft_strlen(var)) == 0 &&
		mini->env[i][ft_strlen(var)] == '=')
		{
			printf("mini = %s\n", mini->env[i]);
			return (mini->env[i]);
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
	printf("split = %s\n", split[i]);
	str = get_var(mini, split[i]);
	if (!str)
	{
		printf("Variable not found.\n");
		return (1);
	}
	printf("str11111 = %s\n", str);
	env_update(mini, str);
	return (0);
}

// dois string joins para juntar o PATH (split[1]) com "=" e 
// depois com o que vier do echo dollar finish
// atualizar o valor do env com o strdup de todas as strings menos aquela ou aquelas
//  que damos unset

// int	add_env(char ***env, char *add)
// {
// 	char **new env;
// }