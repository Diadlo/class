#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void (*write_t)(int dst, void* src, int size);
typedef void (*read_t)(void* dst, int src, int size);

typedef struct {
    write_t write;
    read_t read;
} memory_access_t;

#define MEM_SIZE1 1024
int g_memory1[MEM_SIZE1];

void mem1_write(int dst, void* src, int size)
{
    memcpy(g_memory1 + dst, src, size);
}

void mem1_read(void* dst, int src, int size)
{
    memcpy(dst, g_memory1 + src, size);
}

bool test(memory_access_t* mem_access)
{
    uint32_t offset = 0x10;
    uint32_t input = 0xDEADBEEF;
    uint32_t output = 0;
    mem_access->write(offset, &input, sizeof(input));
    mem_access->read(&output, offset, sizeof(output));
    return output == input;
}

int main()
{
    memory_access_t mem_access = {
        .write = mem1_write,
        .read = mem1_read
    };

    bool success = test(&mem_access);
    printf("%s\n", success ? "success" : "fail");
}
