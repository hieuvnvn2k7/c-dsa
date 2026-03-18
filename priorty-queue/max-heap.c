#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long u64;
typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} max_heap;

void swap(u64 *a, u64 *b)
{
    u64 c = *a; *a = *b; *b = c;
}

void free_max_heap(max_heap *h)
{
    if (h->data)
    {
        free(h->data); h->data = NULL;
    }
    h->size = 0; h->memory_size = 0;
}

void local_heapify_max(u64 *a, u64 size, u64 cur_root)
{
    while (2*cur_root+1 < size)
    {
        u64 left = 2*cur_root+1, right = 2*cur_root+2;
        u64 largest = left;
        if (right < size && a[right] > a[largest]) largest = right;
        if (a[cur_root] < a[largest]) swap(a + cur_root, a + largest);
        else break;
        cur_root = largest;
    }
}

max_heap heapify(u64 *a, u64 size)
{
    max_heap h; h.size = size; h.memory_size = size;
    u64 *tmp = malloc(size*sizeof(*tmp));
    if (!tmp)
    {
        h.data = NULL; h.size = 0; h.memory_size = 0; return h;
    }
    h.data = tmp;
    memcpy(h.data, a, size*sizeof(*a));
    for (long long i = ((long long)size - 1)/2; i >= 0; i--)
    {
        local_heapify_max(h.data, size, (u64)i);
    }
    return h;
}

u64 pop_max_heap(max_heap *h)
{
    if (h->size == 0) return -1;
    u64 *d = h->data, sz = h->size;
    u64 res = d[0];
    swap(d, d + sz-1);
    sz--;
    h->size--;
    local_heapify_max(d, sz, 0);
    return res;
}

void push_max_heap(max_heap *h, u64 number)
{
    if (h->size == h->memory_size)
    {
        u64 new_cap = 2 * h->memory_size + 1;
        u64 *tmp = realloc(h->data, new_cap * sizeof(*tmp));
        if (!tmp) return;
        h->data = tmp;
        h->memory_size = new_cap;
    }
    h->size++;
    u64 cur = h->size - 1, *d = h->data;
    d[cur] = number;
    while (cur != 0)
    {
        u64 parent = (cur-1)/2;
        if (d[cur] > d[parent]) swap(d + cur, d + parent);
        else break;
        cur = parent;
    }
}