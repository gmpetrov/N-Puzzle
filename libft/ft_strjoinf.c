/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 17:23:23 by ebaudet           #+#    #+#             */
/*   Updated: 2014/06/26 22:09:42 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoinf(char *s1, char *s2, int free_s1, int free_s2)
{
	int		i;
	int		strlen;
	char	*tmp;
	char	*s1_free;
	char	*s2_free;

	s1_free = s1;
	s2_free = s2;
	strlen = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	tmp = (char *)malloc(sizeof(*tmp) * (strlen));
	i = 0;
	if (tmp)
	{
		while (*s1)
			tmp[i++] = *s1++;
		while (*s2)
			tmp[i++] = *s2++;
		tmp[i] = '\0';
		if (free_s1 == 1)
			free(s1_free);
		if (free_s2 == 1)
			free(s2_free);
		return (tmp);
	}
	return (NULL);
}
