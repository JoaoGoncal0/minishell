/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/05 21:44:16 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     export_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[0] == '=')
		{
			printf("export: `%c': not a valid identifier\n", str[i]);
    		return (1);
		}
        if ((str[i] >= 'a' && str[i] <= 'z') || 
        (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') ||
		str[i] == '=')
            return (0);
        i++;
    }
	printf("export: `%c': not a valid identifier\n", str[i]);
    return (1);
}

int		str_compare(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if ((s1[i] == '=' || !s1[i]) && (s2[i] == '=' || !s2[i]))
         return (0);
	return (1);
}

void    export_var(t_vars *mini)
{
    int     i;
    char    **split;

    i = 1;
    split = ft_split(mini->input, ' ');
	mini->new_export = malloc(sizeof(char *) * (mini->exp_len + 10));
	if (!mini->new_export)
		return;
    while (split[i]) 
    {
		mini->exp_len = export_len(mini->export) + 1;
        if (export_check(split[i]) == 0)
        {
			export_update(mini, split[i]);
			i++;
		}
    }
}

void	export_update(t_vars *mini, char *str)
{
	int	i;
	int k;
    int done;
    
	i = 0;
	k = 0;
    done = 0;
	if (!mini->new_export)
    {
        printf("Error: mini->new_export not initialized.\n");
        return;
	}
	while (k < mini->exp_len)
	{
		if (mini->new_export[k])
		{
			free(mini->new_export[k]);
			mini->new_export[k] = NULL;
		}
		k++;
	}
	while (i < mini->exp_len)
	{
		if (mini->export[i] && str_compare(mini->export[i], str) == 0)
		{
			free(mini->new_export[i]);
			mini->new_export[i] = ft_strdup(str);
			i++;
			break;
		}
		else if (!mini->export[i] && done == 0)
		{
            done = 1;
            mini->new_export[i] = ft_strdup(str);
			//printf("Inserido em new_export[%d]: %s\n", i, mini->new_export[i]);
			i++;
			continue;
		}
		else if (mini->export[i] && str_compare(mini->export[i], str) != 0)
			mini->new_export[i] = ft_strdup(mini->export[i]);
		i++;
	}
	mini->new_export[i] = NULL;
	export_update1(mini);
}

void	export_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;
    //int s;

	i = 0;
	j = 0;
	while (i < mini->exp_len)
	{
		if (mini->export[i])
		{
			free(mini->export[i]);
			mini->export[i] = NULL;
		}
		i++;
	}
	//printf("\n\n----- NEW EXPORT ------\n\n\n");
	//s = -1;
	//while (++s < mini->exp_len)
	//	printf("declare -x: %s\n", mini->new_export[s]);
	i = 0;
	temp = realloc(mini->export, sizeof(char *) * (mini->exp_len + 1));
	if (!temp)
		return;
	mini->export = temp;
	while (j < mini->exp_len)
	{
		if (mini->new_export[j])
			mini->export[j] = ft_strdup(mini->new_export[j]);
		else
			mini->export[j] = NULL;
		j++;
    }
	mini->export[j] = NULL;
	sorting_export(mini);
	//printf("\n\n----- UPDATED EXPORT ------\n\n\n");
	//s = -1;
	//while (++s < mini->exp_len)
	//	printf("fake -x %s\n", mini->export[s]);
}

void	exp_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;

	i = 0;
	j = 0;
	while (i < mini->exp_len)
	{
		if (mini->export[i])
		{
			free(mini->export[i]);
			mini->export[i] = NULL;
		}
		i++;
	}
	i = 0;
	temp = realloc(mini->export, sizeof(char *) * (mini->exp_len + 1));
	if (!temp)
		return;
	mini->export = temp;
	while (j < mini->exp_len)
	{
		if (mini->new_export[j])
			mini->export[j] = ft_strdup(mini->new_export[j]);
		else
			mini->export[j] = NULL;
		j++;
	}
	mini->export[j] = NULL;
	//printf("\n\n----- UPDATED EXPORT ------\n\n\n");
	//j = -1;
	//while (++j < mini->exp_len)
	//{
	//	if (!mini->new_export[j])
	//		continue;
	//	printf("%s\n", mini->new_export[j]);
	//}
}

void	exp_update(t_vars *mini, char *str)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	while (k < mini->exp_len)
	{
		if (mini->new_export[k])
		{
			free(mini->new_export[k]);
			mini->new_export[k] = NULL;
		}
		k++;
	}	
	while (i < mini->exp_len)
	{
		if ((mini->export[i] && 
		ft_strncmp(mini->export[i], str, ft_strlen(str)) == 0) ||
		!mini->export[i])
		{
			printf("valor do iiiii = %d\n", i);
			i++;
			continue;
		}
		if (mini->export[i])
		{
			printf("valor do i = %d\n", i);
			mini->new_export[i] = ft_strdup(mini->export[i]);
			printf("mini->new_export = %s\n", mini->export[i]);
			i++;
		}
	}
	mini->new_export[i] = NULL;
	exp_update1(mini);
}