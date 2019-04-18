
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
#define PRE_STATES_NUM_MAX 2
#define FUN_NAME_MAX 16
#define STATES_NUM_MAX 16
#define ECP256_KEY_SIZE             32
#define NISTP_ECP256_KEY_SIZE       (ECP256_KEY_SIZE/sizeof(uint32_t))

#define ATTR_NAME_MAX 16 // the maximum length of an attribute name is 16 chars
#define ATTR_VALUE_MAX 16 // the maximum length of an attribute value is 16 chars
#define DOC_ATTRS_NUM_MAX 16 // the maximum number of attributes in a doc is 16 attrs
#define COLL_ID_MAX 8 // the maximum length of a collection ID is 16 chars
#define COLL_DOCS_NUM_MAX 64 // the maximum number of documents in a collection is 64 docs
#define STATE_COLLS_NUM_MAX 2 // the maximum number of collections that are allowed to exist in a state

#pragma pack(1)
typedef struct _attr_t{
  char name[ATTR_NAME_MAX];
  char value[ATTR_VALUE_MAX];
} attr_t;

typedef struct _doc_t{
  uint8_t attrs_num;
  attr_t attrs[DOC_ATTRS_NUM_MAX];
} doc_t;

typedef struct _coll_t{
  uint8_t docs_num;
  char coll_id[COLL_ID_MAX];
  doc_t docs[COLL_DOCS_NUM_MAX];
} coll_t;

typedef struct _coll_db_t{
  uint8_t coll_num;
  coll_t colls[STATE_COLLS_NUM_MAX];
} coll_db_t;

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
    uint8_t         payload[];
} aes_gcm_data_t;

typedef struct _response_t{
  proof_t pf;
  ec256_signature_t pf_sign;
  aes_gcm_data_t res;
} response_t;

#pragma pack()

#endif /* !_MAIN_H_ */
