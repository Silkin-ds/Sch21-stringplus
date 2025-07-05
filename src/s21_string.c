#include "s21_string.h"

#if defined(__APPLE__) && defined(__MACH__)
#define CUSTOMERROR "Unknown error: "
const char *error[MAXN] = {"Undefined error: 0",
                           "Operation not permitted",
                           "No such file or directory",
                           "No such process",
                           "Interrupted system call",
                           "Input/output error",
                           "Device not configured",
                           "Argument list too long",
                           "Exec format error",
                           "Bad file descriptor",
                           "No child processes",
                           "Resource deadlock avoided",
                           "Cannot allocate memory",
                           "Permission denied",
                           "Bad address",
                           "Block device required",
                           "Resource busy",
                           "File exists",
                           "Cross-device link",
                           "Operation not supported by device",
                           "Not a directory",
                           "Is a directory",
                           "Invalid argument",
                           "Too many open files in system",
                           "Too many open files",
                           "Inappropriate ioctl for device",
                           "Text file busy",
                           "File too large",
                           "No space left on device",
                           "Illegal seek",
                           "Read-only file system",
                           "Too many links",
                           "Broken pipe",
                           "Numerical argument out of domain",
                           "Result too large",
                           "Resource temporarily unavailable",
                           "Operation now in progress",
                           "Operation already in progress",
                           "Socket operation on non-socket",
                           "Destination address required",
                           "Message too long",
                           "Protocol wrong type for socket",
                           "Protocol not available",
                           "Protocol not supported",
                           "Socket type not supported",
                           "Operation not supported",
                           "Protocol family not supported",
                           "Address family not supported by protocol family",
                           "Address already in use",
                           "Can't assign requested address",
                           "Network is down",
                           "Network is unreachable",
                           "Network dropped connection on reset",
                           "Software caused connection abort",
                           "Connection reset by peer",
                           "No buffer space available",
                           "Socket is already connected",
                           "Socket is not connected",
                           "Can't send after socket shutdown",
                           "Too many references: can't splice",
                           "Operation timed out",
                           "Connection refused",
                           "Too many levels of symbolic links",
                           "File name too long",
                           "Host is down",
                           "No route to host",
                           "Directory not empty",
                           "Too many processes",
                           "Too many users",
                           "Disc quota exceeded",
                           "Stale NFS file handle",
                           "Too many levels of remote in path",
                           "RPC struct is bad",
                           "RPC version wrong",
                           "RPC prog. not avail",
                           "Program version wrong",
                           "Bad procedure for program",
                           "No locks available",
                           "Function not implemented",
                           "Inappropriate file type or format",
                           "Authentication error",
                           "Need authenticator",
                           "Device power is off",
                           "Device error",
                           "Value too large to be stored in data type",
                           "Bad executable (or shared library)",
                           "Bad CPU type in executable",
                           "Shared library version mismatch",
                           "Malformed Mach-o file",
                           "Operation canceled",
                           "Identifier removed",
                           "No message of desired type",
                           "Illegal byte sequence",
                           "Attribute not found",
                           "Bad message",
                           "EMULTIHOP (Reserved)",
                           "No message available on STREAM",
                           "ENOLINK (Reserved)",
                           "No STREAM resources",
                           "Not a STREAM",
                           "Protocol error",
                           "STREAM ioctl timeout",
                           "Operation not supported on socket",
                           "Policy not found",
                           "State not recoverable",
                           "Previous owner died",
                           "Interface output queue is full"};
#elif defined(__linux__)
#define CUSTOMERROR "Unknown error "
#define MAXN 134
const char *error[MAXN] = {"Success",
                           "Operation not permitted",
                           "No such file or directory",
                           "No such process",
                           "Interrupted system call",
                           "Input/output error",
                           "No such device or address",
                           "Argument list too long",
                           "Exec format error",
                           "Bad file descriptor",
                           "No child processes",
                           "Resource temporarily unavailable",
                           "Cannot allocate memory",
                           "Permission denied",
                           "Bad address",
                           "Block device required",
                           "Device or resource busy",
                           "File exists",
                           "Invalid cross-device link",
                           "No such device",
                           "Not a directory",
                           "Is a directory",
                           "Invalid argument",
                           "Too many open files in system",
                           "Too many open files",
                           "Inappropriate ioctl for device",
                           "Text file busy",
                           "File too large",
                           "No space left on device",
                           "Illegal seek",
                           "Read-only file system",
                           "Too many links",
                           "Broken pipe",
                           "Numerical argument out of domain",
                           "Numerical result out of range",
                           "Resource deadlock avoided",
                           "File name too long",
                           "No locks available",
                           "Function not implemented",
                           "Directory not empty",
                           "Too many levels of symbolic links",
                           "Unknown error 41",
                           "No message of desired type",
                           "Identifier removed",
                           "Channel number out of range",
                           "Level 2 not synchronized",
                           "Level 3 halted",
                           "Level 3 reset",
                           "Link number out of range",
                           "Protocol driver not attached",
                           "No CSI structure available",
                           "Level 2 halted",
                           "Invalid exchange",
                           "Invalid request descriptor",
                           "Exchange full",
                           "No anode",
                           "Invalid request code",
                           "Invalid slot",
                           "Unknown error 58",
                           "Bad font file format",
                           "Device not a stream",
                           "No data available",
                           "Timer expired",
                           "Out of streams resources",
                           "Machine is not on the network",
                           "Package not installed",
                           "Object is remote",
                           "Link has been severed",
                           "Advertise error",
                           "Srmount error",
                           "Communication error on send",
                           "Protocol error",
                           "Multihop attempted",
                           "RFS specific error",
                           "Bad message",
                           "Value too large for defined data type",
                           "Name not unique on network",
                           "File descriptor in bad state",
                           "Remote address changed",
                           "Can not access a needed shared library",
                           "Accessing a corrupted shared library",
                           ".lib section in a.out corrupted",
                           "Attempting to link in too many shared libraries",
                           "Cannot exec a shared library directly",
                           "Invalid or incomplete multibyte or wide character",
                           "Interrupted system call should be restarted",
                           "Streams pipe error",
                           "Too many users",
                           "Socket operation on non-socket",
                           "Destination address required",
                           "Message too long",
                           "Protocol wrong type for socket",
                           "Protocol not available",
                           "Protocol not supported",
                           "Socket type not supported",
                           "Operation not supported",
                           "Protocol family not supported",
                           "Address family not supported by protocol",
                           "Address already in use",
                           "Cannot assign requested address",
                           "Network is down",
                           "Network is unreachable",
                           "Network dropped connection on reset",
                           "Software caused connection abort",
                           "Connection reset by peer",
                           "No buffer space available",
                           "Transport endpoint is already connected",
                           "Transport endpoint is not connected",
                           "Cannot send after transport endpoint shutdown",
                           "Too many references: cannot splice",
                           "Connection timed out",
                           "Connection refused",
                           "Host is down",
                           "No route to host",
                           "Operation already in progress",
                           "Operation now in progress",
                           "Stale file handle",
                           "Structure needs cleaning",
                           "Not a XENIX named type file",
                           "No XENIX semaphores available",
                           "Is a named type file",
                           "Remote I/O error",
                           "Disk quota exceeded",
                           "No medium found",
                           "Wrong medium type",
                           "Operation canceled",
                           "Required key not available",
                           "Key has expired",
                           "Key has been revoked",
                           "Key was rejected by service",
                           "Owner died",
                           "State not recoverable",
                           "Operation not possible due to RF-kill",
                           "Memory page has hardware error"};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  const char *s = (const char *)str;
  void *first = S21_NULL;
  while (i < n) {
    if (*(unsigned char *)(s + i) == (unsigned char)c) {
      first = (void *)(s + i);
      break;
    }
    i++;
  }
  return first;
}
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  s21_size_t i = 0;
  const unsigned char *cstr1 = (const unsigned char *)str1;
  const unsigned char *cstr2 = (const unsigned char *)str2;
  int result = 0;
  while (i < n && cstr1[i] == cstr2[i]) {
    i++;
  }
  if (i < n) {
    result = (int)(cstr1[i] - cstr2[i]);
  }
  return result;
}
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t i = 0;
    while (i++ < n) *(((char *)dest) + (i - 1)) = *(((char *)src) + (i - 1));
  }
  return dest;
}
void *s21_memset(void *str, int c, s21_size_t n) {
  if (str != S21_NULL) {
    unsigned char *ptr_str = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
      ptr_str[i] = (unsigned char)c;
    }
  }
  return str;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_length = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest[dest_length++] = src[i];
  }
  return dest;
}
char *s21_strchr(const char *str, int c) {
  s21_size_t str_length = s21_strlen(str);
  char *result = S21_NULL;
  for (s21_size_t i = 0; i < str_length; i++) {
    if (str[i] == c) {
      result = (char *)str + i;
      break;
    }
  }
  return result;
}
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int diff = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] && str1[i] != '\0') {
      diff = str1[i] - str2[i];
      break;
    }
  }
  if (diff > 0) diff = 1;
  if (diff == 0) diff = 0;
  if (diff < 0) diff = -1;
  return diff;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  // Дополнение нулями оставшихся байт
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);
  int lens = 0;
  s21_size_t i = 0;
  s21_size_t lenght = 0;
  for (; i < len_str1; i++) {
    if (lens) break;
    for (s21_size_t j = 0; j < len_str2; j++) {
      if (str1[i] == str2[j]) {
        lenght = i;
        lens++;
      }
    }
  }
  if (!lens) lenght = i;
  return lenght;
}
char *s21_strerror(int errnum) {
  static char buffer[50];

  if (errnum <= MAXN && errnum >= 0) {
    s21_strncpy(buffer, (char *)error[errnum], sizeof(buffer) - 1);
  } else {
    s21_sprintf(buffer, "%s%d", CUSTOMERROR, errnum);
  }
  return buffer;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;

  const char *temp;

  temp = str;

  while (*temp != '\0') {
    count++;
    temp++;
  }

  return count;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  char *result = S21_NULL;
  for (int i = 0; str1[i] != '\0' && flag == 0; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        ++flag;
        result = (char *)str1 + i;
      }
    }
  }
  return result;
}
char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  int i = (int)s21_strlen(str);
  while (i >= 0) {
    if (str[i] == (char)c) {
      result = ((char *)(str + i));
      break;
    }
    --i;
  }
  return result;
}
char *s21_strstr(const char *haystack, const char *needle) {
  const char *buf;
  int flag = 0;
  int len = (int)s21_strlen(needle);
  if (len == 0) {
    buf = haystack;
    flag = 1;
  } else {
    while (*haystack) {
      if (*haystack == *needle) {
        int j = 0;
        while (*haystack == *(needle + j) && *(needle + j) != '\0') {
          j++;
          haystack++;
        }
        if (j == len) {
          flag = 1;
          haystack = haystack - len;
          break;
        }
      } else
        haystack++;
    }
    buf = haystack;
  }
  return !flag ? S21_NULL : (char *)buf;
}
int strtok_check(char ch, const char *str) {
  int flag = 0;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == ch) {
      flag = 1;
      break;
    }
    i++;
  }
  return flag;
}
char *s21_strtok(char *str, const char *delim) {
  static char *current = S21_NULL;
  char *result = S21_NULL;
  if (str) current = str;
  if (current && delim) {
    while (strtok_check(*current, delim) && *current != '\0')
      current++;  // skip razdelitel
    if (*current != '\0') {
      result = current;
      while (strtok_check(*current, delim) == 0 && *current != '\0')
        current++;  // skip token
      if (*current != '\0') {
        *current = '\0';
        current++;
      } else {
        current = S21_NULL;
      }
    } else {
      current = S21_NULL;
    }
  }
  return (char *)result;
}
void *s21_to_lower(const char *str) {
  char *res = S21_NULL;

  if (str != S21_NULL) {
    int len = s21_strlen(str);
    res = (char *)malloc(len + 1);
    if (res != S21_NULL) {
      for (int i = 0; i <= len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
          res[i] = str[i] + 32;
        else
          res[i] = str[i];
      }
    }
  }

  return res;
}
void *s21_to_upper(const char *str) {
  char *res = S21_NULL;

  if (str != S21_NULL) {
    int len = s21_strlen(str);
    res = (char *)malloc(len + 1);
    if (res != S21_NULL) {
      for (int i = 0; i <= len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
          res[i] = str[i] - 32;
        else
          res[i] = str[i];
      }
    }
  }

  return res;
}
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  s21_size_t src_length, str_length;
  src_length = (src == S21_NULL) ? 0 : s21_strlen(src);
  str_length = (str == S21_NULL) ? 0 : s21_strlen(str);
  s21_size_t fin_length = src_length + str_length;
  if (start_index <= src_length) {
    res = (char *)calloc(src_length + str_length + 1, sizeof(char));
  }
  if (res) {
    for (s21_size_t i = 0; i < fin_length; i++) {
      if (i < start_index) {
        res[i] = src[i];
      } else if (i < str_length + start_index) {
        res[i] = str[i - start_index];
      } else {
        res[i] = src[i - str_length];
      }
    }
  }
  return res;
}
void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;

  if (src != S21_NULL) {
    int len = s21_strlen(src);
    int start = 0, end = len;
    char default_chars[7] = " \t\n\v\r\f\0";
    if (trim_chars == S21_NULL || s21_strlen(trim_chars) == 0)
      trim_chars = default_chars;

    while (start < len && s21_strchr(trim_chars, src[start]) != S21_NULL)
      start++;
    while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL)
      end--;

    if (end <= start) {
      res = (char *)malloc(1);
      if (res != S21_NULL) *res = '\0';
    } else {
      res = (char *)malloc(end - start + 1);
      if (res != S21_NULL) {
        s21_memcpy(res, src + start, end - start);
        res[end - start] = '\0';
      }
    }
  }

  return res;
}