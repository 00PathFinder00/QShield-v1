#include "enclave_u.h"
#include <errno.h>

typedef struct ms_e_pairing_init_t {
	sgx_status_t ms_retval;
	char* ms_s;
	size_t ms_count;
} ms_e_pairing_init_t;

typedef struct ms_e_projector_t {
	sgx_status_t ms_retval;
	struct p_pred_s ms_p_pred;
	const char* ms_s_in;
	size_t ms_s_in_len;
	char* ms_s_out;
} ms_e_projector_t;

typedef struct ms_e_selector_t {
	sgx_status_t ms_retval;
	struct s_pred_s ms_s_pred;
	const char* ms_s_in;
	size_t ms_s_in_len;
	char* ms_s_out;
} ms_e_selector_t;

typedef struct ms_e_aggregator_t {
	sgx_status_t ms_retval;
	struct a_pred_s ms_a_pred;
	const char* ms_s_in;
	size_t ms_s_in_len;
	char* ms_s_out;
} ms_e_aggregator_t;

typedef struct ms_e_joiner_t {
	sgx_status_t ms_retval;
	struct j_pred_s ms_j_pred;
	const char* ms_s_in_1;
	size_t ms_s_in_1_len;
	const char* ms_s_in_2;
	size_t ms_s_in_2_len;
	char* ms_s_out;
} ms_e_joiner_t;

typedef struct ms_o_print_str_t {
	const char* ms_str;
} ms_o_print_str_t;

static sgx_status_t SGX_CDECL enclave_o_print_str(void* pms)
{
	ms_o_print_str_t* ms = SGX_CAST(ms_o_print_str_t*, pms);
	o_print_str(ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_enclave = {
	1,
	{
		(void*)enclave_o_print_str,
	}
};
sgx_status_t e_pairing_init(sgx_enclave_id_t eid, sgx_status_t* retval, char* s, size_t count)
{
	sgx_status_t status;
	ms_e_pairing_init_t ms;
	ms.ms_s = s;
	ms.ms_count = count;
	status = sgx_ecall(eid, 0, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t e_projector(sgx_enclave_id_t eid, sgx_status_t* retval, struct p_pred_s p_pred, const char* s_in, char s_out[128])
{
	sgx_status_t status;
	ms_e_projector_t ms;
	ms.ms_p_pred = p_pred;
	ms.ms_s_in = s_in;
	ms.ms_s_in_len = s_in ? strlen(s_in) + 1 : 0;
	ms.ms_s_out = (char*)s_out;
	status = sgx_ecall(eid, 1, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t e_selector(sgx_enclave_id_t eid, sgx_status_t* retval, struct s_pred_s s_pred, const char* s_in, char s_out[128])
{
	sgx_status_t status;
	ms_e_selector_t ms;
	ms.ms_s_pred = s_pred;
	ms.ms_s_in = s_in;
	ms.ms_s_in_len = s_in ? strlen(s_in) + 1 : 0;
	ms.ms_s_out = (char*)s_out;
	status = sgx_ecall(eid, 2, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t e_aggregator(sgx_enclave_id_t eid, sgx_status_t* retval, struct a_pred_s a_pred, const char* s_in, char s_out[128])
{
	sgx_status_t status;
	ms_e_aggregator_t ms;
	ms.ms_a_pred = a_pred;
	ms.ms_s_in = s_in;
	ms.ms_s_in_len = s_in ? strlen(s_in) + 1 : 0;
	ms.ms_s_out = (char*)s_out;
	status = sgx_ecall(eid, 3, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t e_joiner(sgx_enclave_id_t eid, sgx_status_t* retval, struct j_pred_s j_pred, const char* s_in_1, const char* s_in_2, char s_out[128])
{
	sgx_status_t status;
	ms_e_joiner_t ms;
	ms.ms_j_pred = j_pred;
	ms.ms_s_in_1 = s_in_1;
	ms.ms_s_in_1_len = s_in_1 ? strlen(s_in_1) + 1 : 0;
	ms.ms_s_in_2 = s_in_2;
	ms.ms_s_in_2_len = s_in_2 ? strlen(s_in_2) + 1 : 0;
	ms.ms_s_out = (char*)s_out;
	status = sgx_ecall(eid, 4, &ocall_table_enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

