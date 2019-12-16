#include <time.h>
#include <stdint.h>

#include "sgx_urts.h"

#include "enclave_u.h"

#include "naive_operators.h"
#include "main.h"

#define MAX_BUF_LEN 100

#if HAVE_CONFIG_H
#include <config.h>
#endif

typedef struct _state_idx_t e_state_idx_t;
typedef struct _pred_t e_pred_t;

void o_print_str(const char* str){
  printf("%s", str);
}


char* gen_rand_str(int length)
{
	int flag, i;
	char* string;
	srand((unsigned) time(NULL ));
	if ((string = (char*) malloc(length)) == NULL )
	{
		printf("Malloc failed!flag:14\n");
		return NULL ;
	}

	for (i = 0; i < length - 1; i++)
	{
		flag = rand() % 3;
		switch (flag)
		{
			case 0:
				string[i] = 'A' + rand() % 26;
				break;
			case 1:
				string[i] = 'a' + rand() % 26;
				break;
			case 2:
				string[i] = '0' + rand() % 10;
				break;
			default:
				string[i] = 'x';
				break;
		}
	}
	string[length - 1] = '\0';
	return string;
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

int main(int argc, char** argv)
{

  char param[10240];
  FILE *fp = stdin;
  int docs_n;
  if(argc > 2){
    fp = fopen(argv[1], "r");
    if(!fp){
      printf("Error opening %s\n", argv[1]);
    }
    docs_n = atoi(argv[2]);
  }else{
    printf("Usage: .\\QShield <param_path> <docs_num>\n");
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

  /***********************************************************************
   *                data and predicates construction                     *
   ***********************************************************************/
   void *msg = (void *)malloc(sizeof(coll_db_t));
   {
     (((coll_db_t *)msg))->coll_num = 1;
     ((coll_db_t *)msg)->colls[0].docs_num = docs_n;
     memcpy((((coll_db_t *)msg))->colls[0].coll_id, "C1", 3);
     for(int i = 0; i < docs_n; i++){
       (((coll_db_t *)msg))->colls[0].docs[i].attrs_num = 2;
       memcpy((((coll_db_t *)msg))->colls[0].docs[i].attrs[0].name, "a1", 3);
       memcpy((((coll_db_t *)msg))->colls[0].docs[i].attrs[0].value, "11", 3);
       memcpy((((coll_db_t *)msg))->colls[0].docs[i].attrs[1].name, "a3", 3);
       memcpy((((coll_db_t *)msg))->colls[0].docs[i].attrs[1].value, "1", 2);
     }

     //***********************************************************************//
     // (((coll_db_t *)msg))->coll_num = 2;
     //
     // ((coll_db_t *)msg)->colls[0].docs_num = 3;
     // memcpy((((coll_db_t *)msg))->colls[0].coll_id, "C1", 3);
     // (((coll_db_t *)msg))->colls[0].docs[0].attrs_num = 3;
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[0].name, "a1", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[0].value, "11", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[1].name, "a3", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[1].value, "1", 2);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[2].name, "a5", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[0].attrs[2].value, "12", 3);
     //
     // (((coll_db_t *)msg))->colls[0].docs[1].attrs_num = 3;
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[0].name, "a1", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[0].value, "13", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[1].name, "a3", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[1].value, "2", 2);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[2].name, "a5", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[1].attrs[2].value, "15", 3);
     //
     // (((coll_db_t *)msg))->colls[0].docs[2].attrs_num = 3;
     // memcpy((((coll_db_t *)msg))->colls[0].docs[2].attrs[0].name, "a1", 3);
     // memcpy((((coll_db_t *)msg))->colls[0].docs[2].attrs[0].value, "111", 4);
     // memcpy(((coll_db_t *)msg)->colls[0].docs[2].attrs[1].name, "a3", 3);
     // memcpy(((coll_db_t *)msg)->colls[0].docs[2].attrs[1].value, "13", 3);
     // memcpy(((coll_db_t *)msg)->colls[0].docs[2].attrs[2].name, "a5", 3);
     // memcpy(((coll_db_t *)msg)->colls[0].docs[2].attrs[2].value, "223", 4);
     //
     // ((coll_db_t *)msg)->colls[1].docs_num = 4;
     // memcpy(((coll_db_t *)msg)->colls[1].coll_id, "C2", 3);
     // ((coll_db_t *)msg)->colls[1].docs[0].attrs_num = 3;
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[0].name, "a3", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[0].value, "13", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[1].name, "a4", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[1].value, "1", 2);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[2].name, "a2", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[0].attrs[2].value, "201", 4);
     //
     // ((coll_db_t *)msg)->colls[1].docs[1].attrs_num = 3;
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[0].name, "a3", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[0].value, "1", 2);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[1].name, "a4", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[1].value, "10", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[2].name, "a2", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[1].attrs[2].value, "13", 3);
     //
     // ((coll_db_t *)msg)->colls[1].docs[2].attrs_num = 3;
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[0].name, "a3", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[0].value, "2", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[1].name, "a4", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[1].value, "3", 2);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[2].name, "a2", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[2].attrs[2].value, "1", 2);
     //
     // ((coll_db_t *)msg)->colls[1].docs[3].attrs_num = 3;
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[0].name, "a3", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[0].value, "1", 4);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[1].name, "a4", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[1].value, "15", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[2].name, "a2", 3);
     // memcpy(((coll_db_t *)msg)->colls[1].docs[3].attrs[2].value, "100", 4);
   }

   // assembling predicates for operators
   // select: a1 < 100 [C1]
   pred_t *s_pred = (pred_t *)malloc(sizeof(pred_t));
   {
     s_pred->attrs_num = 1;
     strncpy(s_pred->attr_names[0], "a1", 3);
     strncpy(s_pred->attr_values[0], "20", 3);
     strncpy(s_pred->op, "<",2);
     s_pred->tp = SELECTOR;
     s_pred->colls_num = 1;
     strncpy(s_pred->colls[0], "C1", 3);
   }

   //project: a1 [C1]
   pred_t *p_pred_c1 = (pred_t *)malloc(sizeof(pred_t));
   {
     p_pred_c1->attrs_num = 1;
     strncpy(p_pred_c1->attr_names[0], "a1", 3);
     p_pred_c1->tp = PROJECTOR;
     p_pred_c1->colls_num = 1;
     strncpy(p_pred_c1->colls[0], "C1", 3);
   }

   //project: a3, a5 [C1]
   pred_t *p_pred_c2 = (pred_t *)malloc(sizeof(pred_t));
   {
     p_pred_c2->attrs_num = 2;
     strncpy(p_pred_c2->attr_names[0], "a3", 3);
     strncpy(p_pred_c2->attr_names[1], "a5", 3);
     p_pred_c2->tp = PROJECTOR;
     p_pred_c2->colls_num = 1;
     strncpy(p_pred_c2->colls[0], "C1", 3);
   }

   //join: a3 [C1] = a3 [C1]
   pred_t *j_pred = (pred_t *)malloc(sizeof(pred_t));
   {
     j_pred->attrs_num = 1;
     strncpy(j_pred->attr_names[0], "a3", 3);
     j_pred->tp = JOINER;
     j_pred->colls_num = 2;
     strncpy(j_pred->colls[0], "C1", 3);
     strncpy(j_pred->colls[1], "C1", 3);
   }

   //aggregate: a4 [C1] SUM
   pred_t *a_pred = (pred_t *)malloc(sizeof(pred_t));
   {
     a_pred->attrs_num = 1;
     strncpy(a_pred->attr_names[0], "a3", 3);
     a_pred->tp = AGGREGATOR;
     strncpy(a_pred->fun, "SUM", 4);
     a_pred->colls_num = 1;
     strncpy(a_pred->colls[0], "C1", 3);
   }

   /***********************************************************************
    *                   enclave initialization code                       *
    ***********************************************************************/

  // /* Initialize the enclave */
  // if(initialize_enclave() < 0){
  //   printf("Enter a character before exit ...\n");
  //   getchar();
  //   return -1;
  // }
  //
  // /* Initialize the memory region for states in enclave */
  // sgx_status_t ret = SGX_SUCCESS;
  // {
  //   e_states_init(global_eid);
  //
  //   e_pairing_init(global_eid, &ret, param, count);
  //   if(SGX_SUCCESS != ret){
  //     printf("Enclave initialize pairing error!\n");
  //     sgx_destroy_enclave(global_eid);
  //     return -1;
  //   }else{
  //     printf("Enclave initialize pairing ok!\n");
  //   }
  //
  //   // e_rsa_ecdsa_init(global_eid, &ret, 32, 4);
  //   // if(SGX_SUCCESS != ret){
  //   //   printf("Enclave initialize rsa and ecdsa (signature) error!\n");
  //   //   switch(ret){
  //   //       case SGX_ERROR_INVALID_PARAMETER:
  //   //         printf("Invalid parameter!\n");
  //   //         break;
  //   //       case SGX_ERROR_OUT_OF_MEMORY:
  //   //         printf("Out of memory!\n");
  //   //         break;
  //   //       case SGX_ERROR_UNEXPECTED:
  //   //         printf("Error unexpected\n");
  //   //         break;
  //   //   }
  //   //   sgx_destroy_enclave(global_eid);
  //   //   return -1;
  //   // }else{
  //   //   printf("Enclave initialize rsa and ecdsa (signature) ok!\n");
  //   // }
  //
  // }


  /***********************************************************************
   *                      enclave enc/dec test code                      *
   ***********************************************************************/

  // for(int k = 1000000; k < 1000001; k = k + 1000){
  //   char *tmp = gen_rand_str(k);
  //   void *msg = (void *)malloc(k);
  //   memcpy((char *)msg, tmp, k);
  //   size_t msg_size = k;
  //   size_t ct_size = sizeof(aes_gcm_data_t) + msg_size;
  //   void *ct = (void *)malloc(ct_size);
  //   e_encrypt(global_eid, &ret, (uint8_t *) msg, msg_size, (uint8_t *)ct, ct_size);
  //   if(SGX_SUCCESS != ret){
  //     printf("Enclave encrypt message error!\n");
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
  //     free(tmp);
  //     free(msg);
  //     free(ct);
  //     sgx_destroy_enclave(global_eid);
  //     return -1;
  //   }else{
  //     printf("Enclave encrypt message ok!\n");
  //     free(msg);
  //     free(tmp);
  //   }
  //
  //   #define E_SGX_DEC_RESULT_FILE "./results/escheme_sgx_dec.txt"
  //   #define SGX_DEC_RESULT_FILE "./results/sgx_dec.txt"
  //
  //   clock_t start, end;
  //   double exe_time;
  //   double avg_exe_time = 0.0;
  //
  //    state_idx_t *idx;
  //    {
  //      void *tk = (void *)malloc(1);
  //      void *tmp = (void *)malloc(sizeof(state_idx_t));
  //      for(int v = 0; v < 5; v++){
  //        start = clock();
  //        e_decrypt(global_eid, &ret, (uint8_t *)tk, 1, (uint8_t *)ct, ct_size, tmp);
  //        end = clock();
  //        exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  //        avg_exe_time += exe_time;
  //      }
  //
  //      if(SGX_SUCCESS != ret){
  //        printf("Enclave decrypt ciphers with token error!\n");
  //        switch(ret){
  //            case SGX_ERROR_INVALID_PARAMETER:
  //              printf("Invalid parameter!\n");
  //              break;
  //            case SGX_ERROR_OUT_OF_MEMORY:
  //              printf("Out of memory!\n");
  //              break;
  //            case SGX_ERROR_UNEXPECTED:
  //              printf("Error unexpected\n");
  //              break;
  //        }
  //        free(tk);
  //        free(ct);
  //        sgx_destroy_enclave(global_eid);
  //        return -1;
  //      }else{
  //        printf("Enclave decrypt ciphers with token ok!\n");
  //        free(tk);
  //        free(ct);
  //      }
  //      idx = (state_idx_t *)tmp;
  //    }
  //    printf("state index: repo id - %d, state id - %s\n", idx->repo_id, idx->s_id);
  //
  //    printf("\nwriting to e-scheme dec with sgx result file\n");
  //    write_result(SGX_DEC_RESULT_FILE, k, (avg_exe_time/5));
  //    free(idx);
  // }

  /***********************************************************************
   *                    enclave operator test code                       *
   ***********************************************************************/

  // #define SELECTOR_RESULT_FILE "./results/selector.txt"
  // #define PROJECTOR_RESULT_FILE "./results/projector.txt"
  // #define JOINER_RESULT_FILE "./results/joiner.txt"
  // #define AGGREGATOR_RESULT_FILE "./results/aggregator.txt"
  //
  // clock_t start, end;
  // double exe_time;
  // double avg_exe_time = 0.0;
  // //performing selection over C1 with a1 > 100
  // state_idx_t *s_idx;
  // {
  //   void *s_s_out = (void *)malloc(sizeof(state_idx_t));
  //   for(int v = 0; v < 10; v++){
  //     start = clock();
  //     // e_selector(global_eid, &ret, *s_pred, *idx, s_s_out);
  //     // e_projector(global_eid, &ret, *p_pred_c1, *idx, s_s_out);
  //     e_aggregator(global_eid, &ret, *a_pred, *idx, s_s_out);
  //     // e_joiner(global_eid, &ret, *j_pred, *idx, *idx, s_s_out);
  //     end = clock();
  //     exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  //     avg_exe_time += exe_time;
  //   }
  //
  //   if(SGX_SUCCESS != ret){
  //     printf("Enclave perform selection error!\n");
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
  //     free(s_pred);
  //     sgx_destroy_enclave(global_eid);
  //     return -1;
  //   }else{
  //     printf("Enclave perform selection ok!\n");
  //     free(s_pred);
  //   }
  //   s_idx = (state_idx_t *)s_s_out;
  // }
  // printf("state index: repo id - %d, state id - %s\n", s_idx->repo_id, s_idx->s_id);
  //
  // printf("\nwriting to selector result file\n");
  // write_result(AGGREGATOR_RESULT_FILE, 250, (avg_exe_time/10));

  /* Destroy the enclave */
  // sgx_destroy_enclave(global_eid);

  // void *s_out = (void *)malloc(sizeof(state_idx_t));
  // if(selector(*s_pred, *(state_idx_t *)state_init, s_out)){
  //   printf("selector successfully\n");
  // }else{
  //   printf("selector error\n");
  // }
  //
  // void *p_out = (void *)malloc(sizeof(state_idx_t));
  // if(projector(*p_pred_c1, *(state_idx_t *)state_init, p_out)){
  //   printf("projector successfully\n");
  // }else{
  //   printf("projector error\n");
  // }

  // void *j_out = (void *)malloc(sizeof(state_idx_t));
  // if(joiner(*j_pred, *(state_idx_t *)state_init, *(state_idx_t *)state_init, j_out)){
  //   printf("joiner successfully\n");
  // }else{
  //   printf("joiner error\n");
  // }

  // void *a_out = (void *)malloc(sizeof(state_idx_t));
  // if(aggregator(*a_pred, *(state_idx_t *)j_out, a_out)){
  //   printf("aggregator successfully\n");
  // }else{
  //   printf("aggregator error\n");
  // }

  /***********************************************************************
   *                   naive operator test code                          *
   ***********************************************************************/

  void *state_init = (void *)malloc(sizeof(state_idx_t));
  if(states_init((uint8_t*) msg, state_init)){
    printf("initialize state successfully\n");
  }

  #define NAI_SELECTOR_RESULT_FILE "./results/src/nai_selector.txt"
  #define NAI_PROJECTOR_RESULT_FILE "./results/src/nai_projector.txt"
  #define NAI_JOINER_RESULT_FILE "./results/src/nai_joiner.txt"
  #define NAI_AGGREGATOR_RESULT_FILE "./results/src/nai_aggregator.txt"

  clock_t start, end;
  double exe_time;
  double avg_exe_time = 0.0;

  {
    void *out = (void *)malloc(sizeof(state_idx_t));
    start = clock();
    // selector(*s_pred, *(state_idx_t *)state_init, out);
    // projector(*p_pred_c1, *(state_idx_t *)state_init, out);
    // aggregator(*a_pred, *(state_idx_t *)state_init, out);
    joiner(*j_pred, *(state_idx_t *)state_init, *(state_idx_t *)state_init, out);
    end = clock();
    exe_time = (double) (end - start)/CLOCKS_PER_SEC;
  }

  printf("\nwriting to result file\n");
  write_result(NAI_JOINER_RESULT_FILE, docs_n, exe_time);

  return 0;
}
