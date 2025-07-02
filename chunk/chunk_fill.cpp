//
// Created by vik on 6/30/25.
//
#include "chunk.h"
//TODO: rewrite this function for the new block struct
chunk_t place_block(chunk_t chunk, const Vector3_t size, const Vector3_t position, char block){
    if (position.x < 0 || position.x >= size.x) return chunk;
    if (position.y < 0 || position.y >= size.y) return chunk;
    if (position.z < 0 || position.z >= size.z) return chunk;
    chunk[position.x][position.y][position.z] = block;
    return chunk;
}
int min(const int a, const int b) {
    return (a > b) ? b : a;
}
int max(const int a, const int b) {
    return (a < b) ? b : a;
}

double calculate_distance(const Vector3_t p1, const Vector3_t p2) {
    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) + pow(p1.z - p2.z,2));
}
//TODO: rewrite this function for the new block struct
chunk_t chunk_fill_cuboid(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t p1, const Vector3_t p2, char block) {
    for (int x = min(p1.x, p2.x); x <= max(p1.x, p2.x); x++) {
        for (int y = min(p1.y, p2.y); y <= max(p1.y, p2.y); y++) {
            for (int z = min(p1.z, p2.z); z <= max(p1.z, p2.z); z++) {
                chunk = place_block(chunk, chunk_size, (Vector3_t){x,y,z}, block);
                //render_chunk(chunk, chunk_size);
            }
        }
    }
    return chunk;
}
//TODO: rewrite this function for the new block struct
chunk_t chunk_fill_sphere(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t position, double radius, char block) {
    for (int x = position.x - (int)(ceil(radius));x <= position.x + (int)(ceil(radius));x++) {
        for (int y = position.y - (int)ceil(radius);y <= position.y + (int)ceil(radius);y++) {
            for (int z = position.z - (int)ceil(radius);z <= position.z + (int)ceil(radius);z++) {
                if (calculate_distance(position, (Vector3_t){x,y,z}) < radius) {
                    chunk = place_block(chunk, chunk_size, (Vector3_t){x,y,z}, block);
                    //render_chunk(chunk, chunk_size);
                }
            }
        }
    }
    return chunk;
}
