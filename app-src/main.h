
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
typedef struct _state_idx_t state_idx_t;
typedef struct _pred_t pred_t;
#pragma pack()

/*
 * for the response
 */
#define AES_TAG_SIZE          16
#define AES_IV_SIZE        12
#define PAYLOAD_BUF_MAX 128
#define PRE_STATES_NUM_MAX 2
#define FUN_NAME_MAX 16
#define STATES_NUM_MAX 16
#define ECP256_KEY_SIZE             32
#define NISTP_ECP256_KEY_SIZE       (ECP256_KEY_SIZE/sizeof(uint32_t))

#pragma pack(1)
typedef struct _pre_states_t{
  uint8_t p_sts_num;
  char p_sts[PRE_STATES_NUM_MAX][STATE_ID_MAX];
} pre_states_t;

typedef struct _func_t{
  char func_name[FUN_NAME_MAX];
} func_t;

typedef struct _st_proof_t{
  char s_id[STATE_ID_MAX];
  func_t f;
  pre_states_t p_states;
} st_proof_t;

typedef struct _proof_t{
  uint8_t st_proof_num;
  st_proof_t st_proofs[STATES_NUM_MAX];
} proof_t;

typedef struct ec256_signature_t
{
    uint32_t x[NISTP_ECP256_KEY_SIZE];
    uint32_t y[NISTP_ECP256_KEY_SIZE];
} ec256_signature_t;

typedef struct _aes_gcm_data_t {
    uint8_t         payload_tag[AES_TAG_SIZE];
    uint32_t        payload_size;
    uint8_t         payload[PAYLOAD_BUF_MAX];
} aes_gcm_data_t;

typedef struct _response_t{
  proof_t pf;
  ec256_signature_t pf_sign;
  aes_gcm_data_t res;
} response_t;

#pragma pack()

#endif /* !_MAIN_H_ */
