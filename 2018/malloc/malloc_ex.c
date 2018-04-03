/* An horrible dummy malloc */

#include <sys/types.h>
#include <io.h>
#include <process.h>

void *malloc(size_t size)
{
    void *p;
    p = sbrk(0);
    // If sbrk fails, we return NULL
    if (sbrk(size) == (void*)-1)
        return NULL;
    return p;
}

/*****************************************************************************/
typedef struct s_block *t_block;
struct s_block
{
	size_t		size;
	t_block		next;
	t_block		prev;
	int			free;
	char		data[1];
};

// usage
int test_usage()
{
	t_block			b;
	b = sbrk(0);
	size_t          new_size;
	sbrk(sizeof(struct s_block) + new_size);
}
/*****************************************************************************/
#define align4(x) (((((x)-1)>>2)<<2)+4)
/*****************************************************************************/
t_block base;
t_block find_block(t_block *last, size_t size)
{
	t_block b = base;
	while (b && !(b->free && b->free >= size))
	{
		*last = b;
		b = b->next;
	}
	return (b);
}
/*****************************************************************************/
#define BLOCK_SIZE sizeof(struct s_block)

t_block extend_heap(t_block last, size_t s)
{
	t_block b;
	b = sbrk(0);
	if (sbrk(BLOCK_SIZE + s) == (void*)-1)
		return NULL;
	b->size = s;
	b->next = NULL;
	if (last)
		last->next = b;
	b->free = 0;
	return b;
}

/*****************************************************************************/
void split_block(t_block b, size_t s)
{
	t_block    new;
	new = b->data + s;
	new->size = b->size - s - BLOCK_SIZE;
	new->free = 1;
	b->size = s;
	b->next = new;
}

/*****************************************************************************/
void *malloc(size_t size)
{
	t_block				b, last;
	size_t				s;
	s = align4(size);
	if (base)
	{
		// First find a block
		last = base;
		b = find_block(&last, s);
		if (b)
		{
			// can wo split
			if ((b->size) - s >= (BLOCK_SIZE + 4))
				split_block(b, s);
			b->free = 0;
		}
		else
		{
			// No fitting block, extend the heap
			b = extend_heap(last, s);
			if (!b)
				return NULL;
		}
	}
	else
	{
		// first time
		b = extend_heap(NULL, s);
		if (!b)
			return (NULL);
		base = b;
	}
	return (b->data);
}

void *calloc(size_t number, size_t size)
{
	size_t			*new;
	size_t			s4, i;
	new = malloc(number * size);
	if (new)
	{
		s4 = align4(number * size) << 2;
		for (i = 0; i < s4; i++)
			new[i] = 0;
	}
	return (new);
}

/*****************************************************************************/
t_block fusion(t_block b)
{
	if (b->next && b->next->free)
	{
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
	}
	return (b);
}
/*****************************************************************************/
struct s_block
{
	size_t				size;
	struct s_block		*next;
	struct s_block		*prev;
	int					free;
	void				*ptr;
	char				data[1];
};
typedef struct s_block *t_block;

t_block get_block(void *p)
{
	char *tmp;
	tmp = p;
	return (p = tmp -= BLOCK_SIZE);
}

int valid_addr(void *p)
{
	if (base)
	{
		if (p > base && p < sbrk(0))
		{
			return (p == (get_block(p))->ptr);
		}
	}
	return (0);
}

void free(void *p)
{
	t_block b;
	if (valid_addr(p))
	{
		b = get_block(p);
		b->free = 1;
		if (b->prev && b->prev->free)
			b = fusion(b->prev);
		if (b->next)
			fusion(b);
		else
		{
			if (b->prev)
				b->prev->next = NULL;
			else
				base = NULL;
			brk(b);
		}
	}
}

void copy_block(t_block src, t_block dst)
{
	int				*sdata, *ddata;
	size_t			i;
	sdata = src->ptr;
	ddata = dst->ptr;
	for (i = 0; i * 4 < src->size && i * 4 < dst->size; i++)
		ddata[i] = sdata[i];
}

void *realloc(void *p, size_t size)
{
	size_t			s;
	t_block			b, new;
	void			*newp;
	if (!p)
		return (malloc(size));
	if (valid_addr(p))
	{
		s = align4(size);
		b = get_block(p);
		if (b->size >= s)
		{
			if (b->size - s >= (BLOCK_SIZE + 4))
				split_block(b, s);
		}
		else
		{
			if (b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s)
			{
				fusion(b);
				if (b->size - s >= (BLOCK_SIZE + 4))
					split_block(b, s);
			}
			else
			{
				newp = malloc(s);
				if (!newp)
					return (NULL);
				new = get_block(newp);
				copy_block(b, new);
				free(p);
				return (newp);
			}
		}
		return (p);
	}
	return (NULL);
}
/*****************************************************************************/
void *reallocf(void *p, size_t size)
{
	void *newp;
	newp = reallocf(p, size);
	if (!newp)
		free(p);
	return (newp);
}