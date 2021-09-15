/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:54:12 by junylee           #+#    #+#             */
/*   Updated: 2021/09/15 14:40:43 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len1;
	size_t	len2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (len1--)
	{
		ret[i++] = *s1++;
	}
	while (len2--)
	{
		ret[i++] = *s2++;
	}
	ret[i] = '\0';
	return (ret);
}
