#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "enclave_u.h"
#include "test.h"

extern sgx_enclave_id_t global_eid;

void write_result(const char *res_file, int doc_num, double exe_time){
  FILE *out = fopen(res_file, "a");
  if (out == NULL){
    printf("cannot open file %s\n", res_file);
    return;
  }
  fprintf(out, "%d,%lf\n", doc_num, exe_time);
  fclose(out);
  return;
}

void nai_selector_t(char *file_name, int docs_n, pred_t *s_pred, state_idx_t *s_in){
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  {
    void *out = (void *)malloc(sizeof(state_idx_t));
    start = clock();
    selector(*s_pred, *s_in, out);
    end = clock();
    exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  }

  printf("\nwriting to result file\n");
  write_result(file_name, docs_n, exe_time);
}

void nai_projector_t(char *file_name, int docs_n, pred_t *p_pred, state_idx_t *s_in){
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  {
    void *out = (void *)malloc(sizeof(state_idx_t));
    start = clock();
    projector(*p_pred, *s_in, out);
    end = clock();
    exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  }

  printf("\nwriting to result file\n");
  write_result(file_name, docs_n, exe_time);
}

void nai_aggregator_t(char *file_name, int docs_n, pred_t *a_pred, state_idx_t *s_in){
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  {
    void *out = (void *)malloc(sizeof(state_idx_t));
    start = clock();
    aggregator(*a_pred, *s_in, out);
    end = clock();
    exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  }

  printf("\nwriting to result file\n");
  write_result(file_name, docs_n, exe_time);
}

void nai_joiner_t(char *file_name, int docs_n, pred_t *j_pred, state_idx_t *s_in_1, state_idx_t *s_in_2){
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  {
    void *out = (void *)malloc(sizeof(state_idx_t));
    start = clock();
    joiner(*j_pred, *s_in_1, *s_in_2, out);
    end = clock();
    exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  }

  printf("\nwriting to result file\n");
  write_result(file_name, docs_n, exe_time);
}

void sgx_selector_t(char *file_name, int docs_n, e_pred_t *e_s_pred, e_state_idx_t *s_in){
  sgx_status_t ret = SGX_SUCCESS;
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  void *s_out = (void *)malloc(sizeof(e_state_idx_t));
  start = clock();
  e_selector(global_eid, &ret, *e_s_pred, *s_in, s_out);
  end = clock();
  exe_time = (double) (end - start)/CLOCKS_PER_SEC;

  if(SGX_SUCCESS != ret){
    printf("Enclave perform selection error!\n");
    switch(ret){
      case SGX_ERROR_INVALID_PARAMETER:
        printf("Invalid parameter!\n");
        break;
      case SGX_ERROR_OUT_OF_MEMORY:
        printf("Out of memory!\n");
        break;
      case SGX_ERROR_UNEXPECTED:
        printf("Error unexpected\n");
        break;
    }
    return;
  }else{
    printf("Enclave perform selection ok!\n");
  }

  printf("state index: repo id - %d, state id - %s\n", ((e_state_idx_t *)s_out)->repo_id, ((e_state_idx_t *)s_out)->s_id);

  printf("\nwriting to sgx_selector result file\n");
  write_result(file_name, docs_n, exe_time);
}

void sgx_projector_t(char *file_name, int docs_n, e_pred_t *e_p_pred, e_state_idx_t *s_in){
  sgx_status_t ret = SGX_SUCCESS;
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  void *s_out = (void *)malloc(sizeof(e_state_idx_t));
  start = clock();
  e_projector(global_eid, &ret, *e_p_pred, *s_in, s_out);
  end = clock();
  exe_time = (double) (end - start)/CLOCKS_PER_SEC;

  if(SGX_SUCCESS != ret){
    printf("Enclave perform projection error!\n");
    switch(ret){
      case SGX_ERROR_INVALID_PARAMETER:
        printf("Invalid parameter!\n");
        break;
      case SGX_ERROR_OUT_OF_MEMORY:
        printf("Out of memory!\n");
        break;
      case SGX_ERROR_UNEXPECTED:
        printf("Error unexpected\n");
        break;
    }
    return;
  }else{
    printf("Enclave perform projection ok!\n");
  }

  printf("state index: repo id - %d, state id - %s\n", ((e_state_idx_t *)s_out)->repo_id, ((e_state_idx_t *)s_out)->s_id);

  printf("\nwriting to sgx_projector result file\n");
  write_result(file_name, docs_n, exe_time);
}

void sgx_aggregator_t(char *file_name, int docs_n, e_pred_t *e_a_pred, e_state_idx_t *s_in){
  sgx_status_t ret = SGX_SUCCESS;
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  void *s_out = (void *)malloc(sizeof(e_state_idx_t));
  start = clock();
  e_aggregator(global_eid, &ret, *e_a_pred, *s_in, s_out);
  end = clock();
  exe_time = (double) (end - start)/CLOCKS_PER_SEC;

  if(SGX_SUCCESS != ret){
    printf("Enclave perform aggregation error!\n");
    switch(ret){
      case SGX_ERROR_INVALID_PARAMETER:
        printf("Invalid parameter!\n");
        break;
      case SGX_ERROR_OUT_OF_MEMORY:
        printf("Out of memory!\n");
        break;
      case SGX_ERROR_UNEXPECTED:
        printf("Error unexpected\n");
        break;
    }
    return;
  }else{
    printf("Enclave perform aggregation ok!\n");
  }

  printf("state index: repo id - %d, state id - %s\n", ((e_state_idx_t *)s_out)->repo_id, ((e_state_idx_t *)s_out)->s_id);

  printf("\nwriting to sgx_aggregator result file\n");
  write_result(file_name, docs_n, exe_time);
}

void sgx_joiner_t(char *file_name, int docs_n, e_pred_t *e_j_pred, e_state_idx_t *s_in_1, e_state_idx_t *s_in_2){
  sgx_status_t ret = SGX_SUCCESS;
  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  void *s_out = (void *)malloc(sizeof(e_state_idx_t));
  start = clock();
  e_joiner(global_eid, &ret, *e_j_pred, *s_in_1, *s_in_2, s_out);
  end = clock();
  exe_time = (double) (end - start)/CLOCKS_PER_SEC;

  if(SGX_SUCCESS != ret){
    printf("Enclave perform join error!\n");
    switch(ret){
      case SGX_ERROR_INVALID_PARAMETER:
        printf("Invalid parameter!\n");
        break;
      case SGX_ERROR_OUT_OF_MEMORY:
        printf("Out of memory!\n");
        break;
      case SGX_ERROR_UNEXPECTED:
        printf("Error unexpected\n");
        break;
    }
    return;
  }else{
    printf("Enclave perform join ok!\n");
  }

  printf("state index: repo id - %d, state id - %s\n", ((e_state_idx_t *)s_out)->repo_id, ((e_state_idx_t *)s_out)->s_id);

  printf("\nwriting to sgx_joiner result file\n");
  write_result(file_name, docs_n, exe_time);
}
