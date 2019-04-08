#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

/*
 * Following structs are defined for the document-oriented data model
 */

#define ATTR_NAME_MAX 16 // the maximum length of an attribute name is 16 chars
#define ATTR_VALUE_MAX 16 // the maximum length of an attribute value is 16 chars

#define DOC_ATTRS_NUM_MAX 16 // the maximum number of attributes in a doc is 16 attrs

#define COLL_ID_MAX 16 // the maximum length of a collection ID is 16 chars
#define COLL_DOCS_NUM_MAX 64 // the maximum number of documents in a collection is 64 docs

#pragma pack(1) // making memory alignment as 1 Byte
typedef struct _attr{
  char name[ATTR_NAME_MAX];
  char value[ATTR_VALUE_MAX];
} attr;

typedef struct _doc{
  uint8_t attrs_num;
  attr attrs[DOC_ATTRS_NUM_MAX];
} doc;

typedef struct _coll{
  uint8_t docs_num;
  char coll_id[COLL_ID_MAX];
  doc docs[COLL_DOCS_NUM_MAX];
} coll;
#pragma pack()

/*
 * Following structs are defined for a state
 */

#define FUN_NAME_MAX 16 // the maximum length of a function name is 16 chars
#define FUN_ID_MAX 16 // the maximum length of a function ID is 16 chars

#define PRE_STATES_NUM_MAX 2 // the maximum number of previous states relied by the function

#define STATE_ID_MAX 16 // the maximum length of a state ID is 16 chars

#define STATE_COLLS_NUM_MAX 2 // the maximum number of collections that are allowed to exist in a state

#pragma pack(1) // making memory alignment as 1 Byte
typedef struct _pre_states{
  uint8_t p_states_num;
  char p_states[PRE_STATES_NUM_MAX][STATE_ID_MAX];
} pre_states;

typedef struct _func{
  char func_name[FUN_NAME_MAX];
} func;

typedef struct _coll_db{
  uint8_t coll_num;
  coll colls[STATE_COLLS_NUM_MAX];
} coll_db;

typedef struct _state{
  uint8_t w; // 1B
  char s_id[STATE_ID_MAX]; //16B
  func f; //16B
  pre_states p_states; // (1+32)B
  coll_db s_db; // (2*(64*(16*(16+16) + 1) + 16 + 1) + 1) = 65699 B
} state; // about 65KB
#pragma pack()

void eprintf(const char *fmt, ...);

#endif
