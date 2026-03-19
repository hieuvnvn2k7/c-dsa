#include <stdbool.h>

typedef unsigned long long u64;
void swap(u64 *a, u64 *b);


typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
    bool (*better)(u64, u64);
} heap;
void free_heap(heap *h);
heap create_empty_heap(u64 memory_size, bool (*better)(u64, u64));
void local_heapify(heap *a, u64 cur_root);
void heapify(heap *a);
heap initialize_heap(u64 *a, u64 size, bool (*better)(u64, u64));
u64 pop_heap(heap *h);
void push_heap(heap *h, u64 data);


typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} max_heap;
void free_max_heap(max_heap *h);
max_heap create_empty_max_heap(u64 memory_size);
void local_heapify_max(u64 *a, u64 size, u64 cur_root);
min_heap heapify_max(u64 *a, u64 size);
u64 pop_max_heap(max_heap *h);
void push_max_heap(max_heap *h, u64 number);


typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} min_heap;
void free_min_heap(min_heap *h);
min_heap create_empty_in_heap(u64 memory_size);
void local_heapify_min(u64 *a, u64 size, u64 cur_root);
min_heap heapify_min(u64 *a, u64 size);
u64 pop_min_heap(min_heap *h);
void push_min_heap(min_heap *h, u64 number);