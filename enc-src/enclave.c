#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include <string.h>

#include "pbc/pbc.h"

#include "enclave.h"
#include "enclave_t.h"

/*
 * enclave global variables
 */

pairing_t g_pairing; //for the used bilinear map

void eprintf(const char *fmt, ...){
  char buf[BUFSIZ] = {'\0'};
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, BUFSIZ, fmt, ap);
  va_end(ap);
  o_print_str(buf);
}

sgx_status_t e_pairing_init(char* param, size_t count){
  eprintf("[Init]: pairing\n");

  sgx_status_t ret = SGX_SUCCESS;

  eprintf("%s\n", param);
  if (count < 0){
    eprintf("[Err]: parameter count error\n");
    ret = SGX_ERROR_UNEXPECTED;
    return ret;
  }

  if(pairing_init_set_buf(g_pairing, param, count)){
    eprintf("[Err]: pairing init failed\n");
    ret = SGX_ERROR_UNEXPECTED;
  }

  return ret;

}
