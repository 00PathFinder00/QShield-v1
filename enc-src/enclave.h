#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#define FUN_NAME_MAX 16
#define FUN_ID_MAX 128

#define PRE_STATES_NUM_MAX 2

#define STATE_ID_MAX 128


struct _pre_states{
  uint8_t p_states_num;
  char p_states[PRE_STATES_NUM_MAX][STATE_ID_MAX];
};

struct _func{
  char func_name[FUN_NAME_MAX];
};

struct _state_body{
  char s_id[STATE_ID_MAX];
  void *s_db;
};

struct state{
  uint8_t w;
  struct _func func;
  struct _pre_states p_states;
  struct _state_body c_state;
};

void eprintf(const char *fmt, ...);

#endif
