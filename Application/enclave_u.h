#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t foo(sgx_enclave_id_t eid, char* buf, size_t len);
sgx_status_t enclaveAdd(sgx_enclave_id_t eid, int* retval, int a, int b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
