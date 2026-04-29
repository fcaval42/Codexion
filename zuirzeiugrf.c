#include "../include/heap.h"

/* ── Comparator ──────────────────────────────────────────────────── */

/*
** Returns 1 if entry A has higher priority than entry B
** (i.e. should be closer to the root = served first).
**
** Primary  : smaller priority value wins (earlier timestamp or deadline).
** Secondary: smaller seq wins (earlier insertion = tie-breaker).
**
** This tie-breaker makes the scheduler fully deterministic even when
** two coders register at the exact same millisecond.
*/
static int	higher_prio(t_heap_entry *a, t_heap_entry *b)
{
	if (a->priority != b->priority)
		return (a->priority < b->priority);
	return (a->seq < b->seq);
}

/* ── Index helpers ───────────────────────────────────────────────── */

static int	parent(int i)
{
	return ((i - 1) / 2);
}

static int	left(int i)
{
	return (2 * i + 1);
}

static int	right(int i)
{
	return (2 * i + 2);
}

/* ── Swap ────────────────────────────────────────────────────────── */

static void	swap(t_heap *h, int i, int j)
{
	t_heap_entry	tmp;

	tmp = h->data[i];
	h->data[i] = h->data[j];
	h->data[j] = tmp;
}

/* ── Bubble up (after push) ──────────────────────────────────────── */

/*
** New element is at index `i`.
** Keep swapping with parent while we have higher priority than parent.
*/
static void	sift_up(t_heap *h, int i)
{
	while (i > 0 && higher_prio(&h->data[i], &h->data[parent(i)]))
	{
		swap(h, i, parent(i));
		i = parent(i);
	}
}

/* ── Bubble down (after pop) ─────────────────────────────────────── */

/*
** Element at root has been replaced by the last leaf.
** Push it down until the heap property is restored.
*/
static void	sift_down(t_heap *h, int i)
{
	int	best;
	int	l;
	int	r;

	while (1)
	{
		best = i;
		l = left(i);
		r = right(i);
		if (l < h->size && higher_prio(&h->data[l], &h->data[best]))
			best = l;
		if (r < h->size && higher_prio(&h->data[r], &h->data[best]))
			best = r;
		if (best == i)
			break ;
		swap(h, i, best);
		i = best;
	}
}

/* ── Public API ──────────────────────────────────────────────────── */

void	heap_init(t_heap *h)
{
	h->size = 0;
	h->seq_counter = 0;
}

/*
** Push a new waiter onto the heap.
** Returns 1 on success, 0 if the heap is full.
*/
int	heap_push(t_heap *h, long priority, int coder_id)
{
	int	i;

	if (h->size >= HEAP_MAX)
		return (0);
	i = h->size;
	h->data[i].priority = priority;
	h->data[i].seq = h->seq_counter++;
	h->data[i].coder_id = coder_id;
	h->size++;
	sift_up(h, i);
	return (1);
}

/*
** Remove and return the highest-priority entry.
** Returns 1 on success, 0 if the heap is empty.
*/
int	heap_pop(t_heap *h, t_heap_entry *out)
{
	if (h->size == 0)
		return (0);
	*out = h->data[0];
	h->size--;
	if (h->size > 0)
	{
		h->data[0] = h->data[h->size];
		sift_down(h, 0);
	}
	return (1);
}

/*
** Peek at the top without removing it.
** Returns 1 on success, 0 if empty.
*/
int	heap_peek(t_heap *h, t_heap_entry *out)
{
	if (h->size == 0)
		return (0);
	*out = h->data[0];
	return (1);
}

int	heap_empty(t_heap *h)
{
	return (h->size == 0);
}