#include <stdlib.h>
#include <stdio.h>

#include "sgx_urts.h"

#include "enclave_u.h"

#include "main.h"

#define MAX_BUF_LEN 100

#if HAVE_CONFIG_H
#include <config.h>
#endif

void o_print_str(const char* str){
  printf("%s", str);
}

sgx_enclave_id_t global_eid = 0;
int initialize_enclave(void)
{
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;

    /* Call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
      printf("main: error %#x,failed to create enclave\n",ret );
        return -1;
    }

    return 0;
}

int main(int argc, char** argv)
{
  /* Initialize the enclave */
  if(initialize_enclave() < 0){
    printf("Enter a character before exit ...\n");
    getchar();
    return -1;
  }

  /* Initialize the memory region for states in enclave */
  sgx_status_t ret = SGX_SUCCESS;
  {
    e_states_init(global_eid);

    char param[10240];
    FILE *fp = stdin;
    if(argc > 1){
      fp = fopen(argv[1], "r");
      if(!fp){
        printf("Error opening %s\n", argv[1]);
      }
    }else{
      printf("Usage: .\\QShield <param_path>\n");
      sgx_destroy_enclave(global_eid);
      exit(-1);
    }
    size_t count = fread(param, 1, 10240, fp);
    if(!count){
      printf("Input error\n");
      sgx_destroy_enclave(global_eid);
      return -1;
    }
    fclose(fp);

    e_pairing_init(global_eid, &ret, param, count);
    if(SGX_SUCCESS != ret){
      printf("Enclave initialize pairing error!\n");
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave initialize pairing ok!\n");
    }

    e_rsa_ecdsa_init(global_eid, &ret, 32, 4);
    if(SGX_SUCCESS != ret){
      printf("Enclave initialize rsa and ecdsa (signature) error!\n");
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
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave initialize rsa and ecdsa (signature) ok!\n");
    }
  }

  /*
   * Test enclave decryption
   */
  state_idx_t *idx;
  {
    void *tk = (void *)malloc(1);
    void *ct = (void *)malloc(2);
    void *tmp = (void *)malloc(sizeof(state_idx_t));
    e_decrypt(global_eid, &ret, (uint8_t *)tk, 1, (uint8_t *)ct, 2, tmp);
    if(SGX_SUCCESS != ret){
      printf("Enclave decrypt ciphers with token error!\n");
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
      free(tk);
      free(ct);
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave decrypt ciphers with token ok!\n");
      free(tk);
      free(ct);
    }
    idx = (state_idx_t *)tmp;
  }
  printf("state index: repo id - %d, state id - %s\n", idx->repo_id, idx->s_id);

  /*
   * Test enclave operators
   */

  // assembling predicates for operators
  // select: a1 > 100 [C1]
  pred_t *s_pred = (pred_t *)malloc(sizeof(pred_t));
  {
    s_pred->attrs_num = 1;
    strncpy(s_pred->attr_names[0], "a1", 3);
    strncpy(s_pred->attr_values[0], "100", 4);
    strncpy(s_pred->op, "<",2);
    s_pred->tp = SELECTOR;
    s_pred->colls_num = 1;
    strncpy(s_pred->colls[0], "C1", 3);
  }

  //project: a1, a3 [C1]
  pred_t *p_pred_c1 = (pred_t *)malloc(sizeof(pred_t));
  {
    p_pred_c1->attrs_num = 2;
    strncpy(p_pred_c1->attr_names[0], "a1", 3);
    strncpy(p_pred_c1->attr_names[1], "a3", 3);
    p_pred_c1->tp = PROJECTOR;
    p_pred_c1->colls_num = 1;
    strncpy(p_pred_c1->colls[0], "C1", 3);
  }

  //project: a3, a4 [C2]
  pred_t *p_pred_c2 = (pred_t *)malloc(sizeof(pred_t));
  {
    p_pred_c2->attrs_num = 2;
    strncpy(p_pred_c2->attr_names[0], "a3", 3);
    strncpy(p_pred_c2->attr_names[1], "a4", 3);
    p_pred_c2->tp = PROJECTOR;
    p_pred_c2->colls_num = 1;
    strncpy(p_pred_c2->colls[0], "C2", 3);
  }

  //join: a3 [C1] = a3 [C2]
  pred_t *j_pred = (pred_t *)malloc(sizeof(pred_t));
  {
    j_pred->attrs_num = 1;
    strncpy(j_pred->attr_names[0], "a3", 3);
    j_pred->tp = JOINER;
    j_pred->colls_num = 2;
    strncpy(j_pred->colls[0], "C1", 3);
    strncpy(j_pred->colls[1], "C2", 3);
  }

  //aggregate: a4 [C1] SUM
  pred_t *a_pred = (pred_t *)malloc(sizeof(pred_t));
  {
    a_pred->attrs_num = 1;
    strncpy(a_pred->attr_names[0], "a4", 3);
    a_pred->tp = AGGREGATOR;
    strncpy(a_pred->fun, "SUM", 4);
    a_pred->colls_num = 1;
    strncpy(a_pred->colls[0], "C1", 3);
  }

  //performing selection over C1 with a1 > 100
  state_idx_t *s_idx;
  {
    void *s_s_out = (void *)malloc(sizeof(state_idx_t));
    e_selector(global_eid, &ret, *s_pred, *idx, s_s_out);
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
      free(s_pred);
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave perform selection ok!\n");
      free(s_pred);
    }
    s_idx = (state_idx_t *)s_s_out;
  }
  printf("state index: repo id - %d, state id - %s\n", s_idx->repo_id, s_idx->s_id);

  // performing projection over C1 on a1, a3
  state_idx_t *p_c1_idx;
  {
    void *p_c1_s_out = (void *)malloc(sizeof(state_idx_t));
    e_projector(global_eid, &ret, *p_pred_c1, *s_idx, p_c1_s_out);
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
      free(p_pred_c1);
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave perform projection ok!\n");
      free(p_pred_c1);
    }
    p_c1_idx = (state_idx_t *)p_c1_s_out;
  }
  printf("state index: repo id - %d, state id - %s\n", p_c1_idx->repo_id, p_c1_idx->s_id);

  //performing projection over C2 on a3, a4
  state_idx_t *p_c2_idx;
  {
    void *p_c2_s_out = (void *)malloc(sizeof(state_idx_t));
    e_projector(global_eid, &ret, *p_pred_c2, *idx, p_c2_s_out);
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
      free(p_pred_c2);
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave perform projection ok!\n");
      free(p_pred_c2);
    }
    p_c2_idx = (state_idx_t *)p_c2_s_out;
  }
  printf("state index: repo id - %d, state id - %s\n", p_c2_idx->repo_id, p_c2_idx->s_id);

  //performing join over C1 and C2 on a3
  state_idx_t *j_idx;
  {
    void *j_s_out = (void *)malloc(sizeof(state_idx_t));
    e_joiner(global_eid, &ret, *j_pred, *p_c1_idx, *p_c2_idx, j_s_out);
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
      free(j_pred);
      sgx_destroy_enclave(global_eid);
      return -1;
    }else{
      printf("Enclave perform join ok!\n");
      free(j_pred);
    }
    j_idx = (state_idx_t *)j_s_out;
  }
  printf("state index: repo id - %d, state id - %s\n", j_idx->repo_id, j_idx->s_id);

  // //performing aggregation over C1 [a4] with sum
  // state_idx_t *a_idx;
  // {
  //   void *a_s_out = (void *)malloc(sizeof(state_idx_t));
  //   e_aggregator(global_eid, &ret, *a_pred, *j_idx, a_s_out);
  //   if(SGX_SUCCESS != ret){
  //     printf("Enclave perform aggregation error!\n");
  //     switch(ret){
  //         case SGX_ERROR_INVALID_PARAMETER:
  //           printf("Invalid parameter!\n");
  //           break;
  //         case SGX_ERROR_OUT_OF_MEMORY:
  //           printf("Out of memory!\n");
  //           break;
  //         case SGX_ERROR_UNEXPECTED:
  //           printf("Error unexpected\n");
  //           break;
  //     }
  //     free(a_pred);
  //     sgx_destroy_enclave(global_eid);
  //     return -1;
  //   }else{
  //     printf("Enclave perform aggregation ok!\n");
  //     free(a_pred);
  //   }
  //   a_idx = (state_idx_t *)a_s_out;
  // }
  // printf("state index: repo id - %d, state id - %s\n", a_idx->repo_id, a_idx->s_id);

  /* Destroy the enclave */
  sgx_destroy_enclave(global_eid);

  return 0;
}
