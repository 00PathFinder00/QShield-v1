
#include <stdio.h>

#include "sgx_urts.h"

#include "enclave_u.h"
#include "main.h"


#define MAX_BUF_LEN 100

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

int main()
{
    char buffer[MAX_BUF_LEN] ="dandan";

    /* Initialize the enclave */
    if(initialize_enclave() < 0){
      printf("Enter a character before exit ...\n");
      getchar();
      return -1;
     }
    foo(global_eid,buffer,MAX_BUF_LEN);
    printf("%s\n",buffer);
    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
    return 0;
}
