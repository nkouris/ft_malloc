/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 16:42:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 13:41:01 by nkouris          ###   ########.fr       */
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
}

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
	/* determine where you are in the page and figure whether or not to
	 * create new tag */
	tag += sizeof(t_mtag) + MTAG->size;
	meta_init(head, tag);
	MTAG->size = unused;
/* add to free tree needed */
	ft_rbinsert(
	return (EXIT_SUCCESS);
}

/*
void	segmeta_init(void *tag, size_t size)
{
	if ((unused = ((nummap * pagesize) - ((tag + sizeof(t_mtag) + MTAG->size) - head))) < (sizeof(t_mtag) + 10))
	{
		MTAG->size += unused;
		return (EXIT_FAILURE);
	}
	else
		tag += sizeof(t_mtag) + MTAG->size;
	
}
*/

void	pagemeta_init(void *head, size_t nummap, size_t size)
{
	void		*tag;
	uint32_t	i;

	i = 0;
	tag = head;
	HTAG->segcount = 1;
	HTAG->nummap = nummap;
	tag += sizeof(t_hdc);
	meta_init(head, tag);
#ifdef DEBUG
	ft_printf("Map head : <%p>\t@ meta : <%p>\t", MTAG->map_head, MTAG);
#endif
	MTAG->size = size;
	freeseg_delim_init(tag);
	tag += sizeof(t_mtag) + MTAG->size;
#ifdef DEBUG
	ft_printf("Size of free seg : <%d>\n", MTAG->size);
#endif
//	}
}
