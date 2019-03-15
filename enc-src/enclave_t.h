#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct p_pred_s {
	uint8_t size;
	char attrs[255][16];
} p_pred_s;

typedef struct s_pred_s {
	char attr_name[16];
	char op[8];
	char attr_value[16];
} s_pred_s;

typedef struct a_pred_s {
	char fun[16];
	char attr_name[16];
} a_pred_s;

typedef struct j_pred_s {
	char attr_name[16];
	char attr_value[16];
} j_pred_s;

sgx_status_t e_pairing_init(char* s, size_t count);
sgx_status_t e_projector(struct p_pred_s p_pred, const char* s_in, char s_out[128]);
sgx_status_t e_selector(struct s_pred_s s_pred, const char* s_in, char s_out[128]);
sgx_status_t e_aggregator(struct a_pred_s a_pred, const char* s_in, char s_out[128]);
sgx_status_t e_joiner(struct j_pred_s j_pred, const char* s_in_1, const char* s_in_2, char s_out[128]);

sgx_status_t SGX_CDECL o_print_str(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
