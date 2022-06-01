#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#ifndef TYPES_H
#define TYPES_H 
extern "C" {
    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t u8;
    typedef int64_t i64;
    typedef int32_t i32;
    typedef int16_t i16;
    typedef int8_t i8;
    typedef uint64_t* u64p;
    typedef uint32_t* u32p;
    typedef uint16_t* u16p;
    typedef uint8_t* u8p;
    typedef int64_t* i64p;
    typedef int32_t* i32p;
    typedef int16_t* i16p;
    typedef int8_t* i8p;
    typedef char* str; 
}
#endif /* TYPES_H */