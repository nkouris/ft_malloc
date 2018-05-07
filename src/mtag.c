/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 16:42:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 17:49:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static inline __attribute__((always_inline))void	meta_init(void *head,
		void *tag) 
{
	MTAG->map_head = head;
	MTAG->parent = NULL;
	MTAG->left = NULL;
	MTAG->right = NULL;
	MTAG->color = RED;
	MTAG->condition = 0;
}

	/* determine where you are in the page and figure whether or not to
	 * create new tag */

static inline __attribute__((always_inline))int	freeseg_delim_init(void *tag)
{
	void		*head;
	uint64_t	unused;
	size_t		pagesize;
	uint16_t	nummap;

	pagesize = (size_t)getpagesize();
	nummap = ((t_hdc *)(MTAG->map_head))->nummap;
	head = MTAG->map_head;
	unused = (nummap * pagesize) - ((tag + sizeof(t_mtag) + MTAG->size) - head);
#ifdef DEBUG
	ft_printf("Size of used seg : <%d>\nPotential unused : %lld\n", MTAG->size,
			unused);
#endif
	tag += sizeof(t_mtag) + MTAG->size;
	meta_init(head, tag);
	MTAG->size = unused;
	MTAG->condition |= UNUSED;
#ifdef DEBUG
	ft_printf("node to insert: <%p>\n", tag);
#endif
	ft_rbinsert(g_tracksegs[EMPTYSEGS], tag);
	return (EXIT_SUCCESS);
}

void		freeseg_use(void *tag, size_t size)
{
	void		*head;
	uint64_t	unused;

	head = MTAG->map_head;
	unused = ((MTAG->size) - (sizeof(t_mtag) + size));
	MTAG->size = size;
	MTAG->condition |= USED;
#ifdef DEBUG
	ft_printf("Size of used seg : <%d>\nPotential unused : %lld\n", MTAG->size,
			unused);
#endif
	tag += sizeof(t_mtag) + MTAG->size;
	meta_init(head, tag);
	MTAG->size = unused;
	MTAG->condition |= UNUSED;
#ifdef DEBUG
	ft_printf("node to insert: <%p>\n", tag);
#endif
	ft_rbinsert(g_tracksegs[EMPTYSEGS], tag);
}

void	pagemeta_init(void *head, size_t nummap, size_t size)
{
	void		*tag;
	uint32_t	i;

	i = 0;
	tag = head;
	HTAG->nummap = nummap;
	HTAG->segcount = 1;
	HTAG->root = NULL;
	if (g_tracksegs[EMPTYSEGS] == NULL)
		g_tracksegs[EMPTYSEGS] = head;
	tag += sizeof(t_hdc);
	meta_init(head, tag);
#ifdef DEBUG
	ft_printf("Map head : <%p>\t@ meta : <%p>\t", MTAG->map_head, MTAG);
#endif
	MTAG->size = size;
	MTAG->condition |= USED;
	freeseg_delim_init(tag);
#ifdef DEBUG
	tag += sizeof(t_mtag) + MTAG->size;
	ft_printf("Free seg added : <%p>\tSize of free seg : <%d>\n", tag, MTAG->size);
#endif
}
