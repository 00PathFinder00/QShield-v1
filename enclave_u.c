#include "enclave_u.h"
#include <errno.h>

typedef struct ms_e_pairing_init_t {
	sgx_status_t ms_retval;
	char* ms_s;
	size_t ms_count;
} ms_e_pairing_init_t;

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

