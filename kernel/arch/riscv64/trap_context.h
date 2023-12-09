#include "type.h"

typedef struct {
  usize x[32];
  usize sstatus;
  usize sepc;
  usize kernel_sp; // sp, not stack addr start
  usize user_sp;   // sp, not stack addr start
} pkx_trap_context;
