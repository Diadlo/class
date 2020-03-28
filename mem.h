#ifndef MEM_H__
#define MEM_H__

#include <stdbool.h>

struct memory_ctx_s;
typedef struct memory_ctx_s memory_ctx_t;

typedef void (*write_t)(memory_ctx_t* ctx, int dst, void* src, int size);
typedef void (*read_t)(memory_ctx_t* ctx, void* dst, int src, int size);
typedef void (*close_t)(memory_ctx_t* ctx);

struct memory_ctx_s {
    void* opaque; // like "private" in c++

    write_t write;
    read_t read;
    close_t close;
};

void mem1_init(memory_ctx_t* ctx, int mem_size);

#endif // MEM_H__
