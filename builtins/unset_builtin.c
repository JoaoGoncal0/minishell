/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/17 21:58:19 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(t_vars *mini, char *var)
{
	int i;
	char *str;

	i = 0;
	
	while (i < mini->env_len)
	{
		printf("var = %s\n", var);
		if (ft_strncmp(mini->env[i], var, ft_strlen(var)) == 0)
		{
			printf("mini = %s\n", mini->env[i]);
			str = ft_strdup(mini->env[i]);
			printf("str = %s\n", str);
		}
		i++;
			// while (str[j] == var[u] && str[j] != '=' && var[u] != '\0')
			// while ( != '\0')
			// {
			// 	str[j] =
            //     j++;
            //     u++;
            // }
	}
	return (str);
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
	printf("split = %s\n", split[i]);
	str = get_var(mini, split[i]);
	printf("str1 = %s\n", str);
	env_update(mini, str);
	return (0);
}

// dois string joins para juntar o PATH (split[1]) com "=" e 
// depois com o que vier do echo dollar finish
// atualizar o valor do env com o strdup de todas as strings menos aquela ou aquelas
//  que damos unset