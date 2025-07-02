//
// Created by vik on 6/30/25.
//
#include "chunk.h"
#include <cstdlib>
#include <cstdio>
//TODO: rewrite this function for the new block struct
void free_chunk(chunk_t chunk, const Vector3_t size) {
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
}
chunk_t allocate_chunk(const Vector3_t size) {
    chunk_t chunk = static_cast<chunk_t>(calloc(size.x , sizeof *chunk));
    for (int x = 0; x < size.x; x++) {
        chunk[x] = static_cast<char**>(calloc(size.y+ 1 , sizeof **chunk));
        for (int y = 0; y < size.y; y++) {
            chunk[x][y] = static_cast<char*>(calloc(size.z , sizeof ***chunk));
        }
    }
    for (int x = 0; x < size.x; x++) {
        for (int z = 0; z < size.z; z++) {
            chunk[x][0][z] = BLOCK_CANVAS;
        }

    }
    return chunk;
}

chunk_new AllocateChunkNew(const Vector3_t size) {
    chunk_new chunk = static_cast<chunk_new>(calloc(size.x , sizeof *chunk));
    for (int x = 0; x < size.x; x++) {
        chunk[x] = static_cast<Block**>(calloc(size.y+ 1 , sizeof **chunk));
        for (int y = 0; y < size.y; y++) {
            chunk[x][y] = static_cast<Block*>(calloc(size.z , sizeof ***chunk));
            for (int z = 0; z < size.z; z++) {
                chunk[x][y][z].color[0] = 1.0f;
                chunk[x][y][z].color[1] = 1.0f;
                chunk[x][y][z].color[2] = 1.0f;
            }
        }
    }
    return chunk;
}
//TODO: rewrite this function for the new block struct
chunk_t init_chunk(Vector3_t *size) {

    chunk_t chunk = allocate_chunk(*size);
    return chunk;

}
//TODO: rewrite this function for the new block struct
chunk_t read_chunk_file(Vector3_t *chunkSize) {
    FILE *file = fopen("Chunks/1.in", "r");
    if (file == nullptr) return nullptr;
    fscanf(file,"%d%d%d", &chunkSize->x, &chunkSize->y, &chunkSize->z);


    chunk_t chunk = static_cast<chunk_t>(malloc(chunkSize->z * sizeof *chunk));

    for (int x = 0; x < chunkSize->x; x++) {
        chunk[x] = static_cast<char**>(malloc(chunkSize->y * sizeof **chunk));
        for (int y = chunkSize->y-1; y >= 0; y--) {
            chunk[x][y] = static_cast<char*>(malloc(chunkSize->z * sizeof ***chunk));

            for (int z = 0; z < chunkSize->z; z++)
                fscanf(file,"%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}
//TODO: rewrite this function for the new block struct
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const  Vector3_t block_position) {
    if (block_position.x < 0 || block_position.x >= chunk_size.x) {
        printf("ERROR: X coordinate is not valid\n");
        return;
    }
    if (block_position.y < 0 || block_position.y >= chunk_size.y) {
        printf("ERROR: Y coordinate is not valid\n");
        return;
    }
    if (block_position.z < 0 || block_position.z >= chunk_size.z) {
        printf("ERROR: Z coordinate is not valid\n");
        return;
    }
    printf("Block %d at X:%d Y:%d Z:%d\n",chunk[block_position.x][block_position.y][block_position.z],
        block_position.x,block_position.y,block_position.z);
}
//TODO: rewrite this function for the new block struct
void print_chunk(chunk_t chunk, Vector3_t size) {
    printf("Chunk: width-%d, height-%d, depth-%d", size.x, size.y, size.z);
    for (int x  = 0; x < size.x; x++) {
        for (int y  = 0; y < size.y; y++) {
            for (int z  = 0; z < size.z; z++) {
                printf("%d ",chunk[x][y][z]);

            }
            printf("\n");
        }
        printf("\n");
    }

}
//TODO: rewrite this function for the new block struct
chunk_t read_chunk(int *width, int *height, int *depth) {
    scanf("%d%d%d", width, height, depth);

    chunk_t chunk = static_cast<chunk_t>(malloc(*width * sizeof *chunk));

    for (int x = 0; x < *width; x++) {
        chunk[x] = static_cast<char**>(malloc(*height * sizeof **chunk));
        for (int y = *height-1; y >= 0; y--) {
            chunk[x][y] = static_cast<char*>(malloc(*depth * sizeof ***chunk));

            for (int z = 0; z < *depth; z++)
                scanf("%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}
//TODO: rewrite this function for the new block struct
Vector3 intToFloatVec3(const Vector3_t x) {
    Vector3 t;
    t.x = static_cast<float>(x.x);
    t.y = static_cast<float>(x.y);
    t.z = static_cast<float>(x.z);
    return t;
}
//TODO: rewrite this function for the new block struct
Vector3_t floatToIntVec3(const Vector3 x) {
    Vector3_t t;
    t.x = static_cast<int>(x.x);
    t.y = static_cast<int>(x.y);
    t.z = static_cast<int>(x.z);
    return t;
}
