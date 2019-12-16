#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"

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
