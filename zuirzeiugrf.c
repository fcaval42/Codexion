/*
** ================================================================
** BROUILLON SIMPLE POUR LE HEAP
** ================================================================
**
** Ce fichier est volontairement a part pour qu'on avance sans toucher
** au reste du projet.
**
** A quoi sert ce heap dans Codexion ?
** - a garder une liste de coders en attente
** - a toujours recuperer celui qui doit passer en premier
**
** Dans le sujet :
** - FIFO : le premier arrive est servi en premier
** - EDF  : la plus petite deadline passe en premier
**
** Ce fichier n'est pas encore branche au projet.
** Pour l'instant, il sert de base simple a comprendre.
**
** PLUS TARD :
** - les structures + prototypes iront dans "heap.h"
** - les fonctions iront dans "heap.c"
** - l'utilisation de heap_push / heap_pop sera branchee dans la
**   logique d'attente des dongles
*/

#include <stdlib.h>

/*
** ================================================================
** STRUCTURES
** ================================================================
**
** Ces structures devront plus tard aller dans "heap.h".
**
** priority :
** - en FIFO : on peut mettre un compteur d'arrivee
** - en EDF  : on peut mettre la deadline du coder
**
** seq :
** - sert a departager deux priorites egales
** - le plus ancien gagne
**
** coder_id :
** - identifiant du coder concerne
*/

typedef struct s_heap_entry
{
	long			priority;
	unsigned long	seq;
	int				coder_id;
}	t_heap_entry;

typedef struct s_heap
{
	t_heap_entry	*data;
	int				size;
	int				capacity;
	unsigned long	next_seq;
}	t_heap;

/*
** ================================================================
** PROTOTYPES
** ================================================================
**
** Ces prototypes devront plus tard aller dans "heap.h".
*/

int		heap_init(t_heap *heap, int capacity);
void	heap_destroy(t_heap *heap);
int		heap_push(t_heap *heap, long priority, int coder_id);
int		heap_pop(t_heap *heap, t_heap_entry *out);
int		heap_peek(t_heap *heap, t_heap_entry *out);
int		heap_empty(t_heap *heap);

/*
** ================================================================
** FONCTIONS INTERNES
** ================================================================
**
** Ces fonctions peuvent rester "static" dans "heap.c".
*/

static int	has_higher_priority(t_heap_entry a, t_heap_entry b)
{
	if (a.priority < b.priority)
		return (1);
	if (a.priority > b.priority)
		return (0);
	return (a.seq < b.seq);
}

static int	parent_index(int index)
{
	return ((index - 1) / 2);
}

static int	left_index(int index)
{
	return (2 * index + 1);
}

static int	right_index(int index)
{
	return (2 * index + 2);
}

static void	swap_entries(t_heap *heap, int a, int b)
{
	t_heap_entry	tmp;

	tmp = heap->data[a];
	heap->data[a] = heap->data[b];
	heap->data[b] = tmp;
}

/*
** Fait remonter l'element tant qu'il est plus prioritaire que son parent.
*/
static void	sift_up(t_heap *heap, int index)
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

/*
** Fait redescendre l'element tant qu'un enfant est plus prioritaire.
*/
static void	sift_down(t_heap *heap, int index)
{
	int	left;
	int	right;
	int	best;

	while (1)
	{
		left = left_index(index);
		right = right_index(index);
		best = index;
		if (left < heap->size
			&& has_higher_priority(heap->data[left], heap->data[best]))
			best = left;
		if (right < heap->size
			&& has_higher_priority(heap->data[right], heap->data[best]))
			best = right;
		if (best == index)
			break ;
		swap_entries(heap, index, best);
		index = best;
	}
}

/*
** ================================================================
** FONCTIONS PUBLIQUES
** ================================================================
**
** Ces fonctions devront plus tard aller dans "heap.c".
*/

/*
** A appeler pendant l'init.
**
** Plus tard, on pourra faire :
** heap_init(&un_heap, sim->args.nb_coders);
*/
int	heap_init(t_heap *heap, int capacity)
{
	if (!heap || capacity <= 0)
		return (0);
	heap->data = malloc(sizeof(t_heap_entry) * capacity);
	if (!heap->data)
		return (0);
	heap->size = 0;
	heap->capacity = capacity;
	heap->next_seq = 0;
	return (1);
}

/*
** A appeler dans le clean.
*/
void	heap_destroy(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->data);
	heap->data = NULL;
	heap->size = 0;
	heap->capacity = 0;
	heap->next_seq = 0;
}

/*
** Ajoute un coder dans la file de priorite.
**
** Exemples plus tard :
** - FIFO : priority = ordre_arrivee
** - EDF  : priority = deadline_ms
*/
int	heap_push(t_heap *heap, long priority, int coder_id)
{
	int	index;

	if (!heap || !heap->data)
		return (0);
	if (heap->size >= heap->capacity)
		return (0);
	index = heap->size;
	heap->data[index].priority = priority;
	heap->data[index].seq = heap->next_seq;
	heap->data[index].coder_id = coder_id;
	heap->next_seq++;
	heap->size++;
	sift_up(heap, index);
	return (1);
}

/*
** Retire l'element le plus prioritaire.
*/
int	heap_pop(t_heap *heap, t_heap_entry *out)
{
	if (!heap || !heap->data || !out)
		return (0);
	if (heap->size == 0)
		return (0);
	*out = heap->data[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->data[0] = heap->data[heap->size];
		sift_down(heap, 0);
	}
	return (1);
}

/*
** Regarde le premier sans le retirer.
*/
int	heap_peek(t_heap *heap, t_heap_entry *out)
{
	if (!heap || !heap->data || !out)
		return (0);
	if (heap->size == 0)
		return (0);
	*out = heap->data[0];
	return (1);
}

int	heap_empty(t_heap *heap)
{
	if (!heap)
		return (1);
	return (heap->size == 0);
}

/*
** ================================================================
** OU METTRE QUOI PLUS TARD
** ================================================================
**
** 1) Dans "heap.h"
** - t_heap_entry
** - t_heap
** - tous les prototypes publics
**
** 2) Dans "heap.c"
** - toutes les fonctions de ce fichier
**
** 3) Dans "codexion.h"
** - il faudra ajouter un ou plusieurs t_heap dans les structures
**   qui gerent l'attente des dongles
**
** 4) Dans la logique du scheduler
** - quand un coder attend un dongle :
**   -> heap_push(...)
** - quand le dongle choisit le prochain :
**   -> heap_pop(...)
**
** Si tu veux, l'etape suivante on fait juste :
** "comment transformer ce brouillon en vrai heap.h + heap.c"
** sans encore toucher au scheduler.
*/
