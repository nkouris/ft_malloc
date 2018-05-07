/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:58:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/06 18:29:13 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	free_kill(void *ptr, int32_t status)
{
	pid_t	process;

	process = getpid();
	if (status == 1)
		ft_printf("PID: (%llu) Error for object: <%p> <--- Pointer being freed was not allocated\n", process, ptr);
	else
		ft_printf("PID: (%llu) Error for object: <%p> <--- Double free\n",
				process, ptr);
	kill(0, SIGABRT);
}

static inline __attribute__((always_inline))void	free_addition(void *tag,
			uint64_t map_region)
{
	void	*next;

	if ((MTAG->size + tag) != (g_tracksegs[EMPTYSEGS] + map_region))
		next = (tag + sizeof(t_mtag) + MTAG->size);
	else
		next = NULL;
	if (MTAG->condition == UNUSED)
		free_kill(tag, 2);
	ft_bzero((tag + sizeof(t_mtag)), MTAG->size);
	if (next && (NTAG->map_head == g_tracksegs[EMPTYSEGS]) && (NTAG->condition == UNUSED))
	{
#ifdef DEBUG
		ft_printf("concat free segments\n");
#endif
		ft_rbdelete(G_HTAG->root, next);
		MTAG->size += sizeof(t_mtag) + NTAG->size;
		ft_bzero(next, sizeof(t_mtag));
	}
	ft_rbinsert(G_HTAG->root, tag);
}

void	ft_free(void *ptr)
{
	void		*storseg;
	uint64_t	map_region;
	uint64_t	pagesize;

	pagesize = getpagesize();
	if (g_tracksegs[EMPTYSEGS] == NULL)
		free_kill(ptr, 1);
	storseg = g_tracksegs[EMPTYSEGS];
	map_region = (G_HTAG->nummap * pagesize);
	if (ptr < g_tracksegs[EMPTYSEGS])
		free_kill(ptr, 1);
	if ((ptr > (g_tracksegs[EMPTYSEGS] + map_region)) && G_HTAG->next == NULL)
		free_kill(ptr, 1);
	else if ((ptr > (g_tracksegs[EMPTYSEGS] + map_region)) && G_HTAG->next)
	{
		g_tracksegs[EMPTYSEGS] = G_HTAG->next;
		ft_free(ptr);
	}
	else if (((t_mtag *)ptr)->map_head == g_tracksegs[EMPTYSEGS])
		free_addition(ptr, map_region);
	g_tracksegs[EMPTYSEGS] = storseg;
}




	/* pointer bound check */
	/* if yes bzero region else nothing */
	/* set flag to unused */
	/* check region below for possible combination, meaning delete node, add to 
	 * node that will be added */
	/* add node */
