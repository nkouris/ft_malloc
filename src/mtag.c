/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 16:42:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/01 15:16:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#define HTAG ((t_hdc *)tag)
#define MTAG ((t_mtag *)tag)

static inline __attribute__((always_inline))void	meta_init(void *head,
		void *tag) 
{
	MTAG->pghead = head;
	MTAG->parent = NULL;
	MTAG->left = NULL;
	MTAG->right = NULL;
}

static inline __attribute__((always_inline))int	seg_delim_init(void *tag)
{
	void		*head;
	uint64_t	unused;
	size_t		pagesize;
	uint16_t	nummap;

	pagesize = (size_t)getpagesize();
	nummap = ((t_hdc *)(MTAG->pghead))->nummap;
#ifdef DEBUG
	ft_printf("Size of used seg : <%d>\nPotential unused : %lld\n", MTAG->size,
			(pagesize - ((tag + sizeof(t_mtag) + MTAG->size)
			- MTAG->pghead)));
#endif
	if (MTAG->size > pagesize)
		head = MTAG->pghead + (pagesize * (MTAG->size / pagesize));
	else
		head = MTAG->pghead;
	/* determine where you are in the page and figure whether or not to
	 * create new tag */
	if ((unused = ((nummap * pagesize) - ((tag + sizeof(t_mtag) + MTAG->size) - head))) < (sizeof(t_mtag) + 10))
	{
		MTAG->size += unused;
		return (EXIT_FAILURE);
	}
	else if (MTAG->size)
		tag += sizeof(t_mtag) + MTAG->size;
	meta_init(head, tag);
	MTAG->size = unused;
/* add to free tree needed */
	return (EXIT_SUCCESS);
}

void	pagemeta_init(void *head, size_t nummap, size_t size)
{
	void		*tag;
	uint32_t	i;

	i = 0;
	tag = head;
	HTAG->segcount = 1;
	HTAG->nummap = nummap;
	/*
	while (i < nummap)
	{
		if (i)
		{
			size = 0;
			if (MTAG->pghead != head)
			{
				head = MTAG->pghead;
				HTAG->segcount = 0;
			}
			head += (size_t)getpagesize();
			HTAG->segcount = 0;
			tag = head;
		}
		*/
		tag += sizeof(t_hdc);
		meta_init(head, tag);
#ifdef DEBUG
	ft_printf("Page head : <%p>\t@ meta : <%p>\t", MTAG->pghead, MTAG);
#endif
		MTAG->size = size;
		seg_delim_init(tag);
	//	i++;
		tag += sizeof(t_mtag) + MTAG->size;
#ifdef DEBUG
	ft_printf("Size of free seg : <%d>\n", MTAG->size);
#endif
//	}
}
