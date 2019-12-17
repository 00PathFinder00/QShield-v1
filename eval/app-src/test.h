#ifndef _TEST_H_
#define _TEST_H_

#include "naive_operators.h"

typedef struct _state_idx_t e_state_idx_t;
typedef struct _pred_t e_pred_t;

void write_result(const char *res_file, int doc_num, double exe_time);

void nai_selector_t(char *file_name, int docs_n, pred_t *s_pred, state_idx_t *s_in);
void nai_projector_t(char *file_name, int docs_n, pred_t *p_pred, state_idx_t *s_in);
void nai_aggregator_t(char *file_name, int docs_n, pred_t *a_pred, state_idx_t *s_in);
void nai_joiner_t(char *file_name, int docs_n, pred_t *j_pred, state_idx_t *s_in_1, state_idx_t *s_in_2);

void sgx_selector_t(char *file_name, int docs_n, e_pred_t *e_s_pred, e_state_idx_t *e_s_in);
void sgx_projector_t(char *file_name, int docs_n, e_pred_t *e_p_pred, e_state_idx_t *e_s_in);
void sgx_aggregator_t(char *file_name, int docs_n, e_pred_t *e_a_pred, e_state_idx_t *e_s_in);
void sgx_joiner_t(char *file_name, int docs_n, e_pred_t *e_j_pred, e_state_idx_t *e_s_in_1, e_state_idx_t *e_s_in_2);

#endif//_TEST_H_
