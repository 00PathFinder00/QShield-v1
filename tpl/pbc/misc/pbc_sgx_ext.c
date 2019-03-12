#include <stdint.h>
#include <sgx_trts.h>

#include "pbc_sgx_ext.h"

int sgx_rand(){

  uint32_t val;
  sgx_read_rand((unsigned char *)&val, 4);

  return (int)(val/2.0);
}
