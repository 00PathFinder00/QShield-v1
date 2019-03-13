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

  char param[1024];
  FILE *fp = stdin;
  if(argc > 1){
    fp = fopen(argv[1], "r");
    if(!fp){
      printf("Error opening %s\n", argv[1]);
    }
  }else{
    printf("Usage: .\\QShield <param_path>\n");
    exit(-1);
  }
  size_t count = fread(param, 1, 1024, fp);
  if(!count){
    printf("Input error\n");
  }
  fclose(fp);

  char param_a[1024]="type a\nq 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\nh 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\nr 730750818665451621361119245571504901405976559617\nexp2 159\nexp1 107\nsign1 1\nsign0 1\n";

  sgx_status_t ret = SGX_SUCCESS;
  e_pairing_init(global_eid, &ret, param_a, count);
  if(SGX_SUCCESS != ret){
    printf("Enclave initialize pairing error!\n");
  }else{
    printf("Enclave initialize pairing ok!\n");
  }

  /* Destroy the enclave */
  sgx_destroy_enclave(global_eid);

  return 0;
}
