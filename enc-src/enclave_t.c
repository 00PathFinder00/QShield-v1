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

static sgx_status_t SGX_CDECL sgx_e_projector(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_e_projector_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_e_projector_t* ms = SGX_CAST(ms_e_projector_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	const char* _tmp_s_in = ms->ms_s_in;
	size_t _len_s_in = ms->ms_s_in_len ;
	char* _in_s_in = NULL;
	char* _tmp_s_out = ms->ms_s_out;
	size_t _len_s_out = 128 * sizeof(char);
	char* _in_s_out = NULL;

	CHECK_UNIQUE_POINTER(_tmp_s_in, _len_s_in);
	CHECK_UNIQUE_POINTER(_tmp_s_out, _len_s_out);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_s_in != NULL && _len_s_in != 0) {
		_in_s_in = (char*)malloc(_len_s_in);
		if (_in_s_in == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s_in, _len_s_in, _tmp_s_in, _len_s_in)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_s_in[_len_s_in - 1] = '\0';
		if (_len_s_in != strlen(_in_s_in) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	if (_tmp_s_out != NULL && _len_s_out != 0) {
		if ((_in_s_out = (char*)malloc(_len_s_out)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_s_out, 0, _len_s_out);
	}

	ms->ms_retval = e_projector(ms->ms_p_pred, (const char*)_in_s_in, _in_s_out);
err:
	if (_in_s_in) free(_in_s_in);
	if (_in_s_out) {
		if (memcpy_s(_tmp_s_out, _len_s_out, _in_s_out, _len_s_out)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_s_out);
	}

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
	const char* _tmp_s_in = ms->ms_s_in;
	size_t _len_s_in = ms->ms_s_in_len ;
	char* _in_s_in = NULL;
	char* _tmp_s_out = ms->ms_s_out;
	size_t _len_s_out = 128 * sizeof(char);
	char* _in_s_out = NULL;

	CHECK_UNIQUE_POINTER(_tmp_s_in, _len_s_in);
	CHECK_UNIQUE_POINTER(_tmp_s_out, _len_s_out);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_s_in != NULL && _len_s_in != 0) {
		_in_s_in = (char*)malloc(_len_s_in);
		if (_in_s_in == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s_in, _len_s_in, _tmp_s_in, _len_s_in)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_s_in[_len_s_in - 1] = '\0';
		if (_len_s_in != strlen(_in_s_in) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	if (_tmp_s_out != NULL && _len_s_out != 0) {
		if ((_in_s_out = (char*)malloc(_len_s_out)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_s_out, 0, _len_s_out);
	}

	ms->ms_retval = e_selector(ms->ms_s_pred, (const char*)_in_s_in, _in_s_out);
err:
	if (_in_s_in) free(_in_s_in);
	if (_in_s_out) {
		if (memcpy_s(_tmp_s_out, _len_s_out, _in_s_out, _len_s_out)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_s_out);
	}

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
	const char* _tmp_s_in = ms->ms_s_in;
	size_t _len_s_in = ms->ms_s_in_len ;
	char* _in_s_in = NULL;
	char* _tmp_s_out = ms->ms_s_out;
	size_t _len_s_out = 128 * sizeof(char);
	char* _in_s_out = NULL;

	CHECK_UNIQUE_POINTER(_tmp_s_in, _len_s_in);
	CHECK_UNIQUE_POINTER(_tmp_s_out, _len_s_out);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_s_in != NULL && _len_s_in != 0) {
		_in_s_in = (char*)malloc(_len_s_in);
		if (_in_s_in == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s_in, _len_s_in, _tmp_s_in, _len_s_in)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_s_in[_len_s_in - 1] = '\0';
		if (_len_s_in != strlen(_in_s_in) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	if (_tmp_s_out != NULL && _len_s_out != 0) {
		if ((_in_s_out = (char*)malloc(_len_s_out)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_s_out, 0, _len_s_out);
	}

	ms->ms_retval = e_aggregator(ms->ms_a_pred, (const char*)_in_s_in, _in_s_out);
err:
	if (_in_s_in) free(_in_s_in);
	if (_in_s_out) {
		if (memcpy_s(_tmp_s_out, _len_s_out, _in_s_out, _len_s_out)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_s_out);
	}

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
	const char* _tmp_s_in_1 = ms->ms_s_in_1;
	size_t _len_s_in_1 = ms->ms_s_in_1_len ;
	char* _in_s_in_1 = NULL;
	const char* _tmp_s_in_2 = ms->ms_s_in_2;
	size_t _len_s_in_2 = ms->ms_s_in_2_len ;
	char* _in_s_in_2 = NULL;
	char* _tmp_s_out = ms->ms_s_out;
	size_t _len_s_out = 128 * sizeof(char);
	char* _in_s_out = NULL;

	CHECK_UNIQUE_POINTER(_tmp_s_in_1, _len_s_in_1);
	CHECK_UNIQUE_POINTER(_tmp_s_in_2, _len_s_in_2);
	CHECK_UNIQUE_POINTER(_tmp_s_out, _len_s_out);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_s_in_1 != NULL && _len_s_in_1 != 0) {
		_in_s_in_1 = (char*)malloc(_len_s_in_1);
		if (_in_s_in_1 == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s_in_1, _len_s_in_1, _tmp_s_in_1, _len_s_in_1)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_s_in_1[_len_s_in_1 - 1] = '\0';
		if (_len_s_in_1 != strlen(_in_s_in_1) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	if (_tmp_s_in_2 != NULL && _len_s_in_2 != 0) {
		_in_s_in_2 = (char*)malloc(_len_s_in_2);
		if (_in_s_in_2 == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_s_in_2, _len_s_in_2, _tmp_s_in_2, _len_s_in_2)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_s_in_2[_len_s_in_2 - 1] = '\0';
		if (_len_s_in_2 != strlen(_in_s_in_2) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}
	if (_tmp_s_out != NULL && _len_s_out != 0) {
		if ((_in_s_out = (char*)malloc(_len_s_out)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_s_out, 0, _len_s_out);
	}

	ms->ms_retval = e_joiner(ms->ms_j_pred, (const char*)_in_s_in_1, (const char*)_in_s_in_2, _in_s_out);
err:
	if (_in_s_in_1) free(_in_s_in_1);
	if (_in_s_in_2) free(_in_s_in_2);
	if (_in_s_out) {
		if (memcpy_s(_tmp_s_out, _len_s_out, _in_s_out, _len_s_out)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_s_out);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[5];
} g_ecall_table = {
	5,
	{
		{(void*)(uintptr_t)sgx_e_pairing_init, 0},
		{(void*)(uintptr_t)sgx_e_projector, 0},
		{(void*)(uintptr_t)sgx_e_selector, 0},
		{(void*)(uintptr_t)sgx_e_aggregator, 0},
		{(void*)(uintptr_t)sgx_e_joiner, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][5];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, 0, 0, 0, },
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

