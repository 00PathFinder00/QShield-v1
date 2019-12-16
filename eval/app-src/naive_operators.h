#ifndef _NAIVE_OPERATORS_
#define _NAIVE_OPERATORS_

#include "type.h"

enum _pred_type_ {
  PROJECTOR = 1,
  SELECTOR = 2,
  AGGREGATOR = 3,
  JOINER = 4
};

#define OP_SIZE_MAX 8
#define PRED_COLLS_NUM_MAX 2

struct _pred_t_{
  uint8_t attrs_num;
  char attr_names[DOC_ATTRS_NUM_MAX][ATTR_NAME_MAX];
  char attr_values[DOC_ATTRS_NUM_MAX][ATTR_VALUE_MAX];

  enum _pred_type_ tp;

  char op[OP_SIZE_MAX];

  char fun[FUN_NAME_MAX];

  uint8_t colls_num;
  char colls[PRED_COLLS_NUM_MAX][COLL_ID_MAX];
};

struct _state_idx_t_{
  uint8_t repo_id;
  char s_id[STATE_ID_MAX];
};


typedef struct _pred_t_ pred_t;
typedef struct _state_idx_t_ state_idx_t;

bool states_init(uint8_t* msg, void* idx_out);
bool selector(pred_t s_pred, state_idx_t s_in, void* s_out);
bool projector(pred_t p_pred, state_idx_t s_in, void* s_out);
bool aggregator(pred_t a_pred, state_idx_t s_in, void* s_out);
bool joiner(pred_t j_pred, state_idx_t s_in_1, state_idx_t s_in_2, void* s_out);


#endif//_NAIVE_OPERATORS_
