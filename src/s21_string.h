#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUFF_SIZE 512

#if defined(__APPLE__) && defined(__MACH__)
#define MAXN 107
#elif defined(__linux__)
#define MAXN 134
#endif

#define S21_NULL (void *)0
typedef unsigned long long s21_size_t;

typedef struct Specs {
  char specifier;
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int precision;
  int is_precision_set;
  int width;
  char length;
} Specs;

// string
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);  // proverit
int s21_sprintf(char *str, const char *format, ...);

// Основные функции
int s21_sprintf(char *str, const char *format, ...);
int s21_atoi(const char *str);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_isdigit(char c);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
// Форматирование чисел
void whole_num_to_string(int64_t val, char *buffer, int base);
void unsigned_num_to_string(uint64_t val, char *buffer, int base);
void double_to_string(long double val, char *buffer, Specs *spec);
// Парсинг формата
const char *process_format(Specs *spec, const char *pformat, va_list args);
int parce_flags(Specs *spec, const char *pformat);
int parce_width(Specs *spec, const char *pformat, va_list args);
int parce_precision(Specs *spec, const char *pformat, va_list args);
int parce_length(Specs *spec, const char *pformat);
// Обработка спецификаторов
void process_specifier(Specs *spec, char *buffer, va_list args);
void parce_int(Specs *spec, char *buffer, va_list args);
void parse_unsigned(Specs *spec, char *buffer, va_list args);
void parse_octal(Specs *spec, char *buffer, va_list args);
void parse_hex(Specs *spec, char *buffer, va_list args);
void parse_char(Specs *spec, char *buffer, va_list args);
void parse_string(Specs *spec, char *buffer, va_list va);
void parse_pointer(Specs *spec, char *buffer, va_list args);
void parse_float(Specs *spec, char *buffer, va_list args);
void parse_mantiss(Specs *spec, char *buffer, va_list va);
void parse_float_g_G(Specs *spec, char *buffer, va_list va);
// Вспомогательные функции
void format_precision(char *buffer, Specs *spec);
void format_flags(char *buffer, Specs *spec);
void remove_trailing_zeroes(char *buff);
void prepend_mantiss(char *str, int pow, char sign);
void prepend_ox(char *buff, Specs *spec);
bool check_integer_specifier(char c);
bool is_all_zeroes(char *buff);

#endif