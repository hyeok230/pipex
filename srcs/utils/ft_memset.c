/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:51:09 by junylee           #+#    #+#             */
/*   Updated: 2021/09/24 18:52:28 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *ptr, int value, size_t size)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)ptr;
	while (size-- > 0)
	{
		*tmp++ = value;
	}
	return (ptr);
}
