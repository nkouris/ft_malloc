/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:13:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 13:41:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*g_freesegs[2] = {NULL, NULL};

static inline __attribute__((always_inline))size_t	segment_out(size_t pagesize,
		int32_t seg_t, size_t size)
{
	size_t	nummap;

	if (seg_t != LARGE)
	{
		nummap = pagesize / size;
		if (((100 / nummap) * nummap) < 100)
			return ((100 / nummap) + 1);
		else
			return ((100 / nummap) + 1);
	}
	return (((size > pagesize) ? ((size/pagesize) + 1) :
			((pagesize/size) + 1)));
}

static void	*segmap(size_t size, int32_t seg_t)
{
	void	*ret;
	size_t	nummap;
	size_t	pagesize;

#ifdef DEBUG
	ft_printf("size : %d\tseg_type : %s\n", size,
			(seg_t == NORM ? "NORM" : "LARGE"));
#endif
	if (g_freesegs[EMPTYSEGS] != NULL)
	{
		//if ((ret = openseg()))
		//	return (ret);
	}
	pagesize = (size_t)getpagesize();
	nummap = segment_out(pagesize, seg_t, size);
	if ((ret = mmap(NULL, (pagesize * nummap),
		(PROT_READ | PROT_WRITE | PROT_EXEC), (MAP_ANON | MAP_PRIVATE), 0, 0))
		== MAP_FAILED)
		return (NULL);
#ifdef DEBUG
	ft_printf("number of maps : %d\n", nummap);
#endif
	pagemeta_init(ret, nummap, size);
	return ((ret + sizeof(t_mtag)));
}

void	*ft_malloc(size_t size)
{
	void	*ret;
#ifdef DEBUG
	ft_printf("<----ALLOC---->\n");
#endif
	if (!size)
		return (NULL);
	if (size <= TINY || size <= SMALL)
		ret = segmap(size, NORM);
	else
		ret = segmap(size, LARGE);
	if (ret == NULL)
	{
		perror(strerror(errno));
		return (NULL);
	}
	return (ret);
}
