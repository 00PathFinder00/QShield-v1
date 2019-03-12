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


  sgx_status_t ret = SGX_SUCCESS;
  e_pairing_init(global_eid, &ret, param, count);
  if(SGX_SUCCESS != ret){
    printf("Enclave initialize pairing error!\n");
  }else{
    printf("Enclave initialize pairing ok!\n");
  }

  /* Destroy the enclave */
  sgx_destroy_enclave(global_eid);

  return 0;
}
