#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long u64;

typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} min_heap;

void swap(u64 *a, u64 *b)
{
    u64 c = *a; *a = *b; *b = c;
}

void free_min_heap(min_heap *h)
{
    if (h->data)
    {
        free(h->data); h->data = NULL;
    }
    h->size = 0; h->memory_size = 0;
}

void local_heapify_min(u64 *a, u64 size, u64 cur_root)
{
    while (2*cur_root+1 < size)
    {
        u64 left = 2*cur_root+1, right = 2*cur_root+2;
        u64 smallest = left;
        if (right < size && a[smallest] > a[right]) smallest = right;
        if (a[smallest] < a[cur_root]) swap(a + smallest, a + cur_root);
        else break;
        cur_root = smallest;
    }
}

min_heap heapify(u64 *a, u64 size)
{
    min_heap h;
    h.size = size, h.memory_size = size;
    u64 *tmp = malloc(size*sizeof(*tmp));
    if (tmp == NULL)
    {
        h.data = NULL; return h;
    }
    h.data = tmp;
    memcpy(h.data, a, size*(sizeof(*(h.data))));
    for (long long i = ((long long)size-1)/2; i >= 0; i--) local_heapify_min(h.data, size, (u64)i);
    return h;
}

u64 pop_min_heap(min_heap *h)
{
    if (h->size == 0) return -1;
    u64 *d = h->data, sz = h->size, res = d[0];
    swap(d + sz-1, d);
    u64 cur = 0;
    sz--;
    local_heapify_min(h->data, sz, 0);
    h->size--;
    return res;
}

void push_min_heap(min_heap *h, u64 number)
{
    u64 sz = h->size;
    if (sz == h->memory_size)
    {
        u64 *tmp = realloc(h->data, (2 * h->memory_size + 1) * sizeof(*tmp));
        if (tmp == NULL)
        {
            free_min_heap(h); return;
        }
        h->data = tmp;
        h->memory_size = 2 * h->memory_size + 1;
    }
    u64 *d = h->data;
    d[sz++] = number; h->size++;
    int cur = sz-1;
    while (cur != 0)
    {
        if (d[cur] < d[(cur-1)/2]) swap(d + cur, d + (cur-1)/2);
        else break;
        cur = (cur-1)/2;
    }
}