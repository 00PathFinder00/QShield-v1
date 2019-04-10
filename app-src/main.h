
#ifndef _MAIN_H_
#define _MAIN_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

# define TOKEN_FILENAME   "enclave.token"
# define ENCLAVE_FILENAME "enclave.signed.so"

extern sgx_enclave_id_t global_eid;    /* global enclave id */

#define STATE_ID_MAX 16

#pragma pack(1)
typedef struct _state_idx_t{
  uint8_t repo_id;
  char s_id[STATE_ID_MAX];
} state_idx_t;
#pragma pack() 

#endif /* !_MAIN_H_ */
