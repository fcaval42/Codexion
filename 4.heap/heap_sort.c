/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:23:49 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/01 10:51:32 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	sift_up(t_heap *heap, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = parent_index(index);
		if (!has_higher_priority(heap->data[index], heap->data[parent]))
			break ;
		swap_entries(heap, index, parent);
		index = parent;
	}
}

void	sift_down(t_heap *heap, int index)
{
	int	left;
	int	right;
	int	best;

	while (1)
	{
		left = left_index(index);
		right = right_index(index);
		best = index;
		if (left < heap->size && \
			has_higher_priority(heap->data[left], heap->data[best]))
			best = left;
		if (right < heap->size && \
			has_higher_priority(heap->data[right], heap->data[best]))
			best = right;
		if (best == index)
			break ;
		swap_entries(heap, index, best);
		index = best;
	}
}
