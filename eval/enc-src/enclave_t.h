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

typedef enum _pred_type {
	E_PROJECTOR = 1,
	E_SELECTOR = 2,
	E_AGGREGATOR = 3,
	E_JOINER = 4,
} _pred_type;

typedef struct _pred_t {
	uint8_t attrs_num;
	char attr_names[5][4];
	char attr_values[5][4];
	enum _pred_type tp;
	char op[8];
	char fun[16];
	uint8_t colls_num;
	char colls[1][8];
} _pred_t;

typedef struct _state_idx_t {
	uint8_t repo_id;
	char s_id[4];
} _state_idx_t;

void e_states_init(void);
sgx_status_t e_pairing_init(char* s, size_t count);
sgx_status_t e_rsa_ecdsa_init(int n_byte_size, int e_byte_size);
sgx_status_t e_encrypt(uint8_t* msg, size_t msg_size, uint8_t* ct, size_t ct_size);
sgx_status_t e_decrypt(uint8_t* tk, size_t tk_size, uint8_t* ct, size_t ct_size, void* s_idx);
sgx_status_t e_projector(struct _pred_t p_pred, struct _state_idx_t s_in, void* s_out);
sgx_status_t e_selector(struct _pred_t s_pred, struct _state_idx_t s_in, void* s_out);
sgx_status_t e_aggregator(struct _pred_t a_pred, struct _state_idx_t s_in, void* s_out);
sgx_status_t e_joiner(struct _pred_t j_pred, struct _state_idx_t s_in_1, struct _state_idx_t s_in_2, void* s_out);
sgx_status_t e_get_response(struct _state_idx_t s_in, void* res);

sgx_status_t SGX_CDECL o_print_str(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
