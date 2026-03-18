typedef unsigned long long u64;
typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} generic_heap;

void swap(u64 *a, u64 *b);
void free_generic_heap(generic_heap *h);
void local_heapify_generic(u64 *a, u64 size, u64 cur_root, int (*cmp)(u64, u64));
generic_heap heapify_generic(u64 *a, u64 size, int(*cmp)(u64, u64));


typedef struct
{
    u64 size;
    u64 *data;
    u64 memory_size;
} max_heap;
void free_max_heap(max_heap *h);
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
void local_heapify_min(u64 *a, u64 size, u64 cur_root);
min_heap heapify_min(u64 *a, u64 size);
u64 pop_min_heap(min_heap *h);
void push_min_heap(min_heap *h, u64 number);