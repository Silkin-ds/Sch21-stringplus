#include "s21_string.h"

int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  bool overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') str++;

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow)
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    res *= sign;

  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }

  dest[s21_strlen(src)] = '\0';

  return dest;
}
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest;
  char *from = (char *)src;

  char *tmp = (char *)malloc(sizeof(char) * n);

  if (tmp) {
    s21_memcpy(tmp, from, n);
    s21_memcpy(to, tmp, n);
    free(tmp);
  }
  return dest;
}

void whole_num_to_string(int64_t val, char *buffer, int base) {
  char temp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;

  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) temp[idx] = '0';

  while (val > 0) {
    idx--;
    temp[idx] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; temp[idx]; idx++, j++) {
    if (neg && j == 0) {
      buffer[j++] = '-';
    }

    buffer[j] = temp[idx];
  }
}

void unsigned_num_to_string(uint64_t val, char *buffer, int base) {
  char temp[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) {
    temp[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= base)
    temp[idx] = "0123456789abcdef"[val % base];
  for (int j = 0; temp[idx + 1]; idx++, j++) buffer[j] = temp[idx + 1];
}

void format_gG_precision(char *buff, int precision) {
  int sig_digs = 0;
  s21_size_t len = s21_strlen(buff);
  int not_zero_found = 0;
  for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
    if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
      continue;
    else
      not_zero_found = 1;

    if (s21_isdigit(buff[i]) && not_zero_found) {
      sig_digs++;
    }
    if (sig_digs == precision && i + 1 < len) {
      int next = buff[i + 1] == '.' ? 2 : 1;
      buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
      buff[i + 1] = '\0';
      break;
    }
  }
}

void format_wide_string(Specs *spec, char *buff, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (spec->is_precision_set) tmp[spec->precision] = '\0';

  int shift = spec->width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (spec->minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void format_wchar(Specs *spec, char *buff, wchar_t w_c) {
  int flag = 0;
  if (!buff) {
    flag = 1;
  }
  if (!spec->minus && spec->width && flag != 1) {
    char tmp[BUFF_SIZE] = {'\0'};
    wcstombs(tmp, &w_c, BUFF_SIZE);
    for (s21_size_t i = 0; i < spec->width - s21_strlen(tmp); i++)
      buff[i] = ' ';
    s21_strncat(buff, tmp, s21_strlen(tmp));
  } else if (spec->width) {
    wcstombs(buff, &w_c, BUFF_SIZE);
    for (int i = s21_strlen(buff); i < spec->width; i++) buff[i] = ' ';
  } else {
    wcstombs(buff, &w_c, BUFF_SIZE);
  }
}

void format_char(Specs *spec, char *buff, char c) {
  if (!spec->minus && spec->width) {
    for (int i = 0; i < spec->width; i++) {
      buff[i] = ' ';
      if (i == spec->width - 1) buff[i] = c;
    }
  } else if (spec->width) {
    buff[0] = c;
    for (int i = 1; i < spec->width; i++) buff[i] = ' ';
  } else {
    buff[0] = c;
  }
}

void format_string(Specs *spec, char *buff, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (spec->is_precision_set) tmp[spec->precision] = '\0';

  int shift = spec->width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (spec->minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

bool check_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) return true;
  }
  return false;
}

const char *process_format(Specs *spec, const char *pformat, va_list args) {
  int flags = parce_flags(spec, pformat);
  int width = parce_width(spec, pformat + flags, args);
  int precision = parce_precision(spec, pformat + flags + width, args);
  int length = parce_length(spec, pformat + flags + width + precision);

  return pformat + flags + width + precision + length;
}

void parce_unsigned(Specs *spec, char *buffer, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  switch (spec->length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unsigned_num_to_string(val, buffer, 10);
  format_precision(buffer, spec);
  format_flags(buffer, spec);
}

void parce_octal(Specs *spec, char *buffer, va_list args) {
  buffer[0] = '0';
  whole_num_to_string(va_arg(args, int64_t), buffer + spec->hash, 8);
  format_precision(buffer, spec);
  format_flags(buffer, spec);
}

void parce_hex(Specs *spec, char *buff, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  switch (spec->length) {
    case 0:
      val = (uint32_t)val;
      break;
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
  }
  unsigned_num_to_string(val, buff, 16);
  format_precision(buff, spec);
  if (spec->hash) {
    prepend_ox(buff, spec);
  }
  format_flags(buff, spec);
}

void parce_char(Specs *spec, char *buff, va_list args) {
  if (spec->length == 'l') {
    wchar_t w_c;
    w_c = va_arg(args, wchar_t);
    format_wchar(spec, buff, w_c);
  } else {
    char c;
    c = va_arg(args, int);
    format_char(spec, buff, c);
  }
}

void parce_string(Specs *spec, char *buff, va_list args) {
  if (spec->length == 'l') {
    wchar_t *wstr = va_arg(args, wchar_t *);
    format_wide_string(spec, buff, wstr);
  } else {
    char *str = va_arg(args, char *);
    format_string(spec, buff, str);
  }
}

void parce_pointer(Specs *spec, char *buff, va_list args) {
  unsigned_num_to_string(va_arg(args, uint64_t), buff, 16);
  format_precision(buff, spec);
  prepend_ox(buff, spec);
  format_flags(buff, spec);
}

void parce_float(Specs *spec, char *buff, va_list args) {
  long double val = 0;
  if (spec->length == 'L') {
    val = va_arg(args, long double);
  } else {
    val = va_arg(args, double);
  }

  if (!spec->is_precision_set) {
    spec->precision = 6;
  }

  double_to_string(val, buff, spec);
  format_flags(buff, spec);
}

void parce_mantiss(Specs *spec, char *buff, va_list args) {
  long double val = 0;
  if (spec->length == 'L') {
    val = va_arg(args, long double);
  } else {
    val = va_arg(args, double);
  }
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';

  if ((int)val - val) {
    while ((int)val == 0) {
      pow++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }

  if (!spec->is_precision_set) spec->precision = 6;
  double_to_string(val, buff, spec);
  prepend_mantiss(buff, pow, sign);
  format_flags(buff, spec);
}

void parce_float_g_G(Specs *spec, char *buff, va_list va) {
  long double val = 0;
  if (spec->length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!spec->is_precision_set) {
    spec->precision = 6;
  }
  if (spec->precision == 0) spec->precision = 1;
  int precision = spec->precision;
  long double m_val = val;
  int pow = 0;
  if ((int)val - val) {
    while ((int)m_val == 0) {
      pow++;
      m_val *= 10;
    }
  }
  if (pow > 4) {
    spec->precision = 0;
    double_to_string(m_val, buff, spec);
  } else {
    spec->precision = 10;
    double_to_string(val, buff, spec);
  }
  format_gG_precision(buff, precision);
  if (pow > 4) prepend_mantiss(buff, pow, '-');
  remove_trailing_zeroes(buff);
  format_flags(buff, spec);
}

void process_specifier(Specs *spec, char *buffer, va_list args) {
  switch (spec->specifier) {
    case 'd':
    case 'i':
      parce_int(spec, buffer, args);
      break;
    case 'u':
      parce_unsigned(spec, buffer, args);
      break;
    case 'o':
      parce_octal(spec, buffer, args);
      break;
    case 'x':
    case 'X':
      parce_hex(spec, buffer, args);
      break;
    case '%':
      buffer[0] = '%';
      buffer[1] = '\0';
      break;
    case 'c':
      parce_char(spec, buffer, args);
      break;
    case 's':
      parce_string(spec, buffer, args);
      break;
    case 'p':
      parce_pointer(spec, buffer, args);
      break;
    case 'f':
      parce_float(spec, buffer, args);
      break;
    case 'e':
    case 'E':
      parce_mantiss(spec, buffer, args);
      break;
    case 'g':
    case 'G':
      parce_float_g_G(spec, buffer, args);
      break;
  }

  if (spec->specifier == 'G' || spec->specifier == 'E' ||
      spec->specifier == 'X') {
    char *tmp = s21_to_upper(buffer);
    buffer = s21_strcpy(buffer, tmp);
    free(tmp);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  Specs spec = {0};
  va_list args;
  va_start(args, format);

  char *pstr = str;
  const char *pformat = format;

  while (*pformat) {
    if (*pformat != '%') {
      *pstr++ = *pformat++;
      continue;
    } else {
      pformat++;
      s21_memset(&spec, 0, sizeof(spec));
    }

    pformat = process_format(&spec, pformat, args);
    spec.specifier = *pformat;
    pformat++;

    char buffer[BUFF_SIZE] = {'\0'};
    process_specifier(&spec, buffer, args);

    s21_strcpy(pstr, buffer);
    pstr += s21_strlen(buffer);
  }

  *pstr = '\0';
  va_end(args);
  return pstr - str;
}

int parce_flags(Specs *spec, const char *pformat) {
  int counter = 0;
  while (*pformat == '0' || *pformat == '-' || *pformat == '+' ||
         *pformat == ' ' || *pformat == '#') {
    switch (*pformat) {
      case '0':
        spec->zero = true;
        break;
      case '-':
        spec->minus = true;
        break;
      case '+':
        spec->plus = true;
        break;
      case ' ':
        spec->space = true;
        break;
      case '#':
        spec->hash = true;
        break;
    }
    pformat++;
    counter++;
  }
  return counter;
}

int parce_width(Specs *spec, const char *pformat, va_list args) {
  int counter = 0;
  if (*pformat == '*') {  // случай, когда ширина задается в аргументе
    counter++;
    spec->width = va_arg(args, int);  // Необходима проверка?
  } else if (*pformat >= '0' &&
             *pformat <= '9') {  // случай, когда ширина задается в строке
    char temp[BUFF_SIZE] = {'\0'};
    for (int i = 0; *pformat >= '0' && *pformat <= '9'; i++, pformat++) {
      temp[i] = *pformat;
      counter++;
    }
    spec->width = s21_atoi(temp);  // преобразуем строку в число
  }
  return counter;
}

int parce_precision(Specs *spec, const char *pformat, va_list args) {
  int counter = 0;
  if (*pformat == '.') {
    counter++;
    pformat++;
    spec->is_precision_set = true;
  }

  if (*pformat == '*') {  // случай, когда точность задается в аргументе
    counter++;
    pformat++;
    spec->precision = va_arg(args, int);
  }

  if (*pformat >= '0' && *pformat <= '9') {
    char temp[BUFF_SIZE] = {'\0'};
    for (int i = 0; *pformat >= '0' && *pformat <= '9'; i++, pformat++) {
      temp[i] = *pformat;
      counter++;
    }
    spec->precision = s21_atoi(temp);
  }
  return counter;
}

int parce_length(Specs *spec, const char *pformat) {
  int counter = 0;
  switch (*pformat) {
    case 'h':
      spec->length = 'h';
      counter++;
      break;
    case 'l':
      spec->length = 'l';
      counter++;
      break;
    case 'L':
      spec->length = 'L';
      counter++;
  }
  return counter;
}

void parce_int(Specs *spec, char *buffer, va_list args) {
  int64_t val = va_arg(args, int64_t);

  switch (spec->length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }

  whole_num_to_string(val, buffer, 10);
  format_precision(buffer, spec);
  format_flags(buffer, spec);
}

void format_precision(char *buffer, Specs *spec) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = (int)(s21_strlen(buffer));

  if (buffer[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (spec->precision > len) {
    int idx;
    for (idx = sign; idx < spec->precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buffer[i]; i++, idx++) tmp[idx] = buffer[i];

    s21_strcpy(buffer, tmp);
  }

  if (spec->is_precision_set && spec->precision == 0 &&
      check_integer_specifier(spec->specifier) && buffer[0] == '0')
    buffer[0] = '\0';
}

void format_flags(char *buffer, Specs *spec) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (spec->plus && spec->specifier != 'u') {
    tmp[0] = buffer[0] == '-' ? buffer[0] : '+';
    s21_strcpy(tmp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, tmp);
  } else if (spec->space && buffer[0] != '-' && spec->specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buffer);
    s21_strcpy(buffer, tmp);
  }
  if (spec->width > (int)s21_strlen(buffer)) {
    int idx = spec->width - s21_strlen(buffer);
    if (!spec->minus) {
      s21_memset(tmp, spec->zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buffer);
    } else {
      s21_strcpy(tmp, buffer);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buffer, tmp);
  }
}

bool is_all_zeroes(char *buff) {
  for (int i = 0; buff[i]; i++)
    if (buff[i] != '0') return false;
  return true;
}

void prepend_ox(char *buff, Specs *spec) {
  if (!is_all_zeroes(buff) || spec->specifier == 'p') {
    s21_memmove(buff + 2, buff, s21_strlen(buff));
    buff[0] = '0';
    buff[1] = 'x';
  }
}

void double_to_string(long double val, char *ret, Specs *spec) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (spec->precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < spec->precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < spec->precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((spec->is_precision_set && spec->precision != 0) || (int)r ||
      (!spec->is_precision_set && val == 0) || s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buff[idx + 1];
  }
}

void prepend_mantiss(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

void remove_trailing_zeroes(char *buff) {
  int len = s21_strlen(buff);
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    for (int i = len - 1; buff[i] != '.'; i--) {
      if (buff[i] == '0')
        buff[i] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }
