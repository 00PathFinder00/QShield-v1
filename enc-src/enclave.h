#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

/*
 * Following structs are defined for the document-oriented data model
 */

#define ATTR_NAME_MAX 16 // the maximum length of an attribute name is 16 chars
#define ATTR_VALUE_MAX 16 // the maximum length of an attribute value is 16 chars

#define DOC_ATTRS_NUM_MAX 16 // the maximum number of attributes in a doc is 16 attrs

#define COLL_ID_MAX 8 // the maximum length of a collection ID is 16 chars
#define COLL_DOCS_NUM_MAX 64 // the maximum number of documents in a collection is 64 docs

#pragma pack(1) // making memory alignment as 1 Byte
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
#pragma pack()

/*
 * Following structs are defined for states
 */
#define FUN_NAME_MAX 16 // the maximum length of a function name is 16 chars
// #define FUN_ID_MAX 17 // the maximum length of a function ID is 17 chars

#define PRE_STATES_NUM_MAX 2 // the maximum number of previous states relied by the function

#define STATE_ID_MAX 8 // the maximum length of a state ID is 16 chars

#define STATE_COLLS_NUM_MAX 2 // the maximum number of collections that are allowed to exist in a state

#define STATES_NUM_MAX 16 // the maximum number of states allowed by an enclave
#define REQ_PARALLELISM 2 // the maximum requests that are allowed to be processed by enclave in parallel

#pragma pack(1) // making memory alignment as 1 Byte
typedef struct _pre_states_t{
  uint8_t p_sts_num;
  char p_sts[PRE_STATES_NUM_MAX][STATE_ID_MAX];
} pre_states_t;

typedef struct _func_t{
  char func_name[FUN_NAME_MAX];
} func_t;

typedef struct _coll_db_t{
  uint8_t coll_num;
  coll_t colls[STATE_COLLS_NUM_MAX];
} coll_db_t;

typedef struct _state_t{
  uint8_t w; // 1B
  char s_id[STATE_ID_MAX]; //16B
  func_t f; //16B
  pre_states_t p_states; // (1+32)B
  coll_db_t s_db; // (2*(64*(16*(16+16) + 1) + 16 + 1) + 1) = 65699 B
} state_t; // about 65KB

typedef struct _states_t{
 uint8_t states_num;
 bool is_occupied;
 state_t states[STATES_NUM_MAX];
} states_t;

typedef struct _state_idx_t state_idx_t;
typedef struct _pred_t pred_t;

#pragma pack()

void eprintf(const char *fmt, ...);

#endif
