#include "enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


typedef struct ms_e_pairing_init_t {
	sgx_status_t ms_retval;
	char* ms_s;
	size_t ms_count;
} ms_e_pairing_init_t;

typedef struct ms_e_rsa_ecdsa_init_t {
	sgx_status_t ms_retval;
	int ms_n_byte_size;
	int ms_e_byte_size;
} ms_e_rsa_ecdsa_init_t;

typedef struct ms_e_encrypt_t {
	sgx_status_t ms_retval;
	uint8_t* ms_msg;
	size_t ms_msg_size;
	uint8_t* ms_ct;
	size_t ms_ct_size;
} ms_e_encrypt_t;

typedef struct ms_e_decrypt_t {
	sgx_status_t ms_retval;
	uint8_t* ms_tk;
	size_t ms_tk_size;
	uint8_t* ms_ct;
	size_t ms_ct_size;
	void* ms_s_idx;
} ms_e_decrypt_t;

typedef struct ms_e_projector_t {
	sgx_status_t ms_retval;
	struct _pred_t ms_p_pred;
	struct _state_idx_t ms_s_in;
	void* ms_s_out;
} ms_e_projector_t;

typedef struct ms_e_selector_t {
	sgx_status_t ms_retval;
	struct _pred_t ms_s_pred;
	struct _state_idx_t ms_s_in;
	void* ms_s_out;
} ms_e_selector_t;

typedef struct ms_e_aggregator_t {
	sgx_status_t ms_retval;
	struct _pred_t ms_a_pred;
	struct _state_idx_t ms_s_in;
	void* ms_s_out;
} ms_e_aggregator_t;

typedef struct ms_e_joiner_t {
	sgx_status_t ms_retval;
	struct _pred_t ms_j_pred;
	struct _state_idx_t ms_s_in_1;
	struct _state_idx_t ms_s_in_2;
	void* ms_s_out;
} ms_e_joiner_t;

typedef struct ms_e_get_response_t {
	sgx_status_t ms_retval;
	struct _state_idx_t ms_s_in;
	void* ms_res;
} ms_e_get_response_t;

typedef struct ms_o_print_str_t {
	const char* ms_str;
} ms_o_print_str_t;

static sgx_status_t SGX_CDECL sgx_e_states_init(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	e_states_init();
	return status;
}

static sgx_status_t SGX_CDECL sgx_e_pairing_init(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_pairing_init_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_pairing_init_t* ms = SGX_CAST(ms_e_pairing_init_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_s = ms->ms_s;
	size_t _tmp_count = ms->ms_count;
	size_t _len_s = _tmp_count;
	char* _in_s = NULL;

	CHECK_UNIQUE_POINTER(_tmp_s, _len_s);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_s != NULL && _len_s != 0) {
		_in_s = (char*)malloc(_len_s);
		if (_in_s == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s, _len_s, _tmp_s, _len_s)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ms->ms_retval = e_pairing_init(_in_s, _tmp_count);
err:
	if (_in_s) free(_in_s);

	return status;
}

static sgx_status_t SGX_CDECL sgx_e_rsa_ecdsa_init(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_rsa_ecdsa_init_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_rsa_ecdsa_init_t* ms = SGX_CAST(ms_e_rsa_ecdsa_init_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ms->ms_retval = e_rsa_ecdsa_init(ms->ms_n_byte_size, ms->ms_e_byte_size);


	return status;
}

static sgx_status_t SGX_CDECL sgx_e_encrypt(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_encrypt_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_encrypt_t* ms = SGX_CAST(ms_e_encrypt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	uint8_t* _tmp_msg = ms->ms_msg;
	size_t _tmp_msg_size = ms->ms_msg_size;
	size_t _len_msg = _tmp_msg_size;
	uint8_t* _in_msg = NULL;
	uint8_t* _tmp_ct = ms->ms_ct;
	size_t _tmp_ct_size = ms->ms_ct_size;
	size_t _len_ct = _tmp_ct_size;
	uint8_t* _in_ct = NULL;

	CHECK_UNIQUE_POINTER(_tmp_msg, _len_msg);
	CHECK_UNIQUE_POINTER(_tmp_ct, _len_ct);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_msg != NULL && _len_msg != 0) {
		_in_msg = (uint8_t*)malloc(_len_msg);
		if (_in_msg == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_msg, _len_msg, _tmp_msg, _len_msg)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_ct != NULL && _len_ct != 0) {
		if ((_in_ct = (uint8_t*)malloc(_len_ct)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_ct, 0, _len_ct);
	}

	ms->ms_retval = e_encrypt(_in_msg, _tmp_msg_size, _in_ct, _tmp_ct_size);
err:
	if (_in_msg) free(_in_msg);
	if (_in_ct) {
		if (memcpy_s(_tmp_ct, _len_ct, _in_ct, _len_ct)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_ct);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_e_decrypt(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_decrypt_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_decrypt_t* ms = SGX_CAST(ms_e_decrypt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	uint8_t* _tmp_tk = ms->ms_tk;
	size_t _tmp_tk_size = ms->ms_tk_size;
	size_t _len_tk = _tmp_tk_size;
	uint8_t* _in_tk = NULL;
	uint8_t* _tmp_ct = ms->ms_ct;
	size_t _tmp_ct_size = ms->ms_ct_size;
	size_t _len_ct = _tmp_ct_size;
	uint8_t* _in_ct = NULL;
	void* _tmp_s_idx = ms->ms_s_idx;

	CHECK_UNIQUE_POINTER(_tmp_tk, _len_tk);
	CHECK_UNIQUE_POINTER(_tmp_ct, _len_ct);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_tk != NULL && _len_tk != 0) {
		_in_tk = (uint8_t*)malloc(_len_tk);
		if (_in_tk == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_tk, _len_tk, _tmp_tk, _len_tk)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_ct != NULL && _len_ct != 0) {
		_in_ct = (uint8_t*)malloc(_len_ct);
		if (_in_ct == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_ct, _len_ct, _tmp_ct, _len_ct)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ms->ms_retval = e_decrypt(_in_tk, _tmp_tk_size, _in_ct, _tmp_ct_size, _tmp_s_idx);
err:
	if (_in_tk) free(_in_tk);
	if (_in_ct) free(_in_ct);

	return status;
}

static sgx_status_t SGX_CDECL sgx_e_projector(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_projector_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_projector_t* ms = SGX_CAST(ms_e_projector_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_s_out = ms->ms_s_out;



	ms->ms_retval = e_projector(ms->ms_p_pred, ms->ms_s_in, _tmp_s_out);


	return status;
}

static sgx_status_t SGX_CDECL sgx_e_selector(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_selector_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_selector_t* ms = SGX_CAST(ms_e_selector_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_s_out = ms->ms_s_out;



	ms->ms_retval = e_selector(ms->ms_s_pred, ms->ms_s_in, _tmp_s_out);


	return status;
}

static sgx_status_t SGX_CDECL sgx_e_aggregator(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_aggregator_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_aggregator_t* ms = SGX_CAST(ms_e_aggregator_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_s_out = ms->ms_s_out;



	ms->ms_retval = e_aggregator(ms->ms_a_pred, ms->ms_s_in, _tmp_s_out);


	return status;
}

static sgx_status_t SGX_CDECL sgx_e_joiner(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_joiner_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_joiner_t* ms = SGX_CAST(ms_e_joiner_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_s_out = ms->ms_s_out;



	ms->ms_retval = e_joiner(ms->ms_j_pred, ms->ms_s_in_1, ms->ms_s_in_2, _tmp_s_out);


	return status;
}

static sgx_status_t SGX_CDECL sgx_e_get_response(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_get_response_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_get_response_t* ms = SGX_CAST(ms_e_get_response_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_res = ms->ms_res;



	ms->ms_retval = e_get_response(ms->ms_s_in, _tmp_res);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[10];
} g_ecall_table = {
	10,
	{
		{(void*)(uintptr_t)sgx_e_states_init, 0},
		{(void*)(uintptr_t)sgx_e_pairing_init, 0},
		{(void*)(uintptr_t)sgx_e_rsa_ecdsa_init, 0},
		{(void*)(uintptr_t)sgx_e_encrypt, 0},
		{(void*)(uintptr_t)sgx_e_decrypt, 0},
		{(void*)(uintptr_t)sgx_e_projector, 0},
		{(void*)(uintptr_t)sgx_e_selector, 0},
		{(void*)(uintptr_t)sgx_e_aggregator, 0},
		{(void*)(uintptr_t)sgx_e_joiner, 0},
		{(void*)(uintptr_t)sgx_e_get_response, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][10];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL o_print_str(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_o_print_str_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_o_print_str_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	ocalloc_size += (str != NULL) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_o_print_str_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_o_print_str_t));
	ocalloc_size -= sizeof(ms_o_print_str_t);

	if (str != NULL) {
		ms->ms_str = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
	}
	
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

