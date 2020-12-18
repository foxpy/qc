#pragma once
#include <stdint.h>

void qc_u64_to_be(uint8_t dst[static 8], uint64_t src);
void qc_u64_to_le(uint8_t dst[static 8], uint64_t src);
void qc_i64_to_be(uint8_t dst[static 8], int64_t src);
void qc_i64_to_le(uint8_t dst[static 8], int64_t src);

void qc_u32_to_be(uint8_t dst[static 4], uint32_t src);
void qc_u32_to_le(uint8_t dst[static 4], uint32_t src);
void qc_i32_to_be(uint8_t dst[static 4], int32_t src);
void qc_i32_to_le(uint8_t dst[static 4], int32_t src);

void qc_u16_to_be(uint8_t dst[static 2], uint16_t src);
void qc_u16_to_le(uint8_t dst[static 2], uint16_t src);
void qc_i16_to_be(uint8_t dst[static 2], int16_t src);
void qc_i16_to_le(uint8_t dst[static 2], int16_t src);

void qc_fp64_to_be(uint8_t dst[static 8], double src);
void qc_fp64_to_le(uint8_t dst[static 8], double src);
void qc_fp32_to_be(uint8_t dst[static 4], float src);
void qc_fp32_to_le(uint8_t dst[static 4], float src);


uint64_t qc_u64_from_be(uint8_t const src[static 8]);
uint64_t qc_u64_from_le(uint8_t const src[static 8]);
int64_t qc_i64_from_be(uint8_t const src[static 8]);
int64_t qc_i64_from_le(uint8_t const src[static 8]);

uint32_t qc_u32_from_be(uint8_t const src[static 4]);
uint32_t qc_u32_from_le(uint8_t const src[static 4]);
int32_t qc_i32_from_be(uint8_t const src[static 4]);
int32_t qc_i32_from_le(uint8_t const src[static 4]);

uint16_t qc_u16_from_be(uint8_t const src[static 2]);
uint16_t qc_u16_from_le(uint8_t const src[static 2]);
int16_t qc_i16_from_be(uint8_t const src[static 2]);
int16_t qc_i16_from_le(uint8_t const src[static 2]);

double qc_fp64_from_be(uint8_t const src[static 8]);
double qc_fp64_from_le(uint8_t const src[static 8]);
float qc_fp32_from_be(uint8_t const src[static 4]);
float qc_fp32_from_le(uint8_t const src[static 4]);
