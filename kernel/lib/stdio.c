#include "type.h"
#include "pkx_arch.h"

#include "./stdio.h"
#include "./stdarg.h"
#include "./string.h"
#include "./utils.h"

isize get_place_holder(
  const char *fmt, usize fmtl, usize now
) {
  if (now >= fmtl) return -1;
  if (fmt[now++] != '%') return -1;
  while (now < fmtl) {
    if (fmt[now] == 'd'
      || fmt[now] == 's'
      || fmt[now] == 'x'
    ) return now;
    now++;
  }
  return -1;
}

void pkx_itoa_stack(isize i, char *ret) {
  if (i == 0) {
    ret[0] = '0';
    ret[1] = 0;
    return;
  }
  
  usize digit = 0;
  bool neg = false;

  if (i < 0) {
    i = -i;
    neg = true;
    digit++;
  }

  isize cpi = i;
  while (cpi) {
    digit++;
    cpi /= 10;
  }

  usize cur = 0;
  while (i) {
    ret[cur++] = i%10+'0';
    i /= 10;
  }
  if (neg)
    ret[cur++] = '-';
  ret[cur] = 0;
  pkx_strrev(ret);
}

void pkx_fmt(const char *fmt, va_list ap) {
  usize l = pkx_strlen(fmt), cur = 0;
  while (cur < l) {
    if (fmt[cur] != '%') {
      pkx_putchar(fmt[cur++]);
      continue;
    }

    char type_index = get_place_holder(fmt, l, cur);
    if (type_index == -1) return;

    char tmpstr[100];
    switch (fmt[type_index]) {
      case 's':
        pkx_puts(va_arg(ap, char*));
        break;
      case 'd':
        pkx_itoa_stack(va_arg(ap, i32), tmpstr);
        pkx_puts(tmpstr);
        break;
      case 'x':
        pkx_print_hex(va_arg(ap, usize));
        break;
      default:
        break;
    }
    cur = type_index+1;
  }
}

void pkx_printk(const char *fmt, ...) {
  #ifdef PKX_NO_PRINTK
  return;
  #endif
  pkx_puts("[kernel] ");
  va_list ap;
  va_start(ap, fmt);
  pkx_fmt(fmt, ap);
  va_end(ap);
}

void pkx_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  pkx_fmt(fmt, ap);
  va_end(ap);
}

void pkx_devide_line(const char *header) {
  #ifdef PKX_NO_PRINTK
  return;
  #endif
  if (pkx_strlen(header) > 20)
    pkx_panic("Invalid devide line header.");
  pkx_printk("");
  usize cur = 0;
  while (header[cur])
    pkx_putchar(header[cur++]);
  pkx_putchar(' ');
  while (cur++ < 30)
    pkx_putchar('-');
  pkx_putchar('\n');
}
