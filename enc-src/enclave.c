#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include <string.h>

#include <sgx_tcrypto.h>

#include "pbc/pbc.h"

#include "enclave.h"
#include "enclave_t.h"

/*
 * enclave global variables
 */

pairing_t g_pairing; //for the bilinear map
errmsg_s_ptr g_errmsg;

void *g_rsa_pri_key;
void *g_rsa_pub_key;
sgx_ec256_private_t *g_ecdsa_sign_key;
sgx_ec256_public_t *g_ecdsa_verify_key;

void eprintf(const char *fmt, ...){
  char buf[BUFSIZ] = {'\0'};
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, BUFSIZ, fmt, ap);
  va_end(ap);
  o_print_str(buf);
}

sgx_status_t e_pairing_init(char* param, size_t count){
  eprintf("[Init]: pairing\n");

  sgx_status_t ret = SGX_SUCCESS;

  eprintf("param = %s, size = %d\n", param, count);
  if (count < 0){
    eprintf("[Err]: parameter count error\n");
    ret = SGX_ERROR_UNEXPECTED;
    return ret;
  }

  sgx_init_errmsg();
  if(pairing_init_set_buf(g_pairing, param, count)){
    eprintf("[Err]: pairing init failed\n");
    ret = SGX_ERROR_UNEXPECTED;
  }
  g_errmsg = sgx_get_errmsg();
  for(int i = 0; i < g_errmsg->err_num; i++){
    eprintf("[Pbc Debug %d]: %s\n",i, g_errmsg->errs[i].msg);
  }
  sgx_clear_errmsg();

  return ret;

}

sgx_status_t e_rsa_ecdsa_init(int n_byte_size, int e_byte_size){
  sgx_status_t ret = SGX_SUCCESS;

  unsigned char *p_e = (unsigned char *)malloc(e_byte_size);   // unsigned char p_e[4] = {1, 0, 1, 0};
  *p_e = '1';
  *(p_e+1) = '0';
  *(p_e+2) = '1';
  *(p_e+3) = '0';
  unsigned char *p_n = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_d = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_p = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_q = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_dmp1 = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_dmq1 = (unsigned char *)malloc(n_byte_size);
  unsigned char *p_iqmp = (unsigned char *)malloc(n_byte_size);

  sgx_ecc_state_handle_t ecc_handle;
  g_ecdsa_sign_key= (sgx_ec256_private_t *)malloc(32);
  g_ecdsa_verify_key = (sgx_ec256_public_t *)malloc(32);

  ret = sgx_create_rsa_key_pair(n_byte_size, e_byte_size, p_n, p_d, p_e, p_p, p_q, p_dmp1, p_dmq1, p_iqmp);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: creating rsa key pair components failed\n");
    return ret;
  }
  ret = sgx_create_rsa_priv2_key(n_byte_size, e_byte_size, p_e, p_p, p_q, p_dmp1, p_dmq1, p_iqmp, &g_rsa_pri_key);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: creating rsa private key failed\n");
    return ret;
  }
  ret = sgx_create_rsa_pub1_key(n_byte_size, e_byte_size, p_n, p_e, &g_rsa_pub_key);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: creating rsa public key failed\n");
    return ret;
  }

  ret = sgx_ecc256_open_context(&ecc_handle);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: ecc256 context open failed\n");
    return ret;
  }
  ret = sgx_ecc256_create_key_pair(g_ecdsa_sign_key, g_ecdsa_verify_key, ecc_handle);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: creating signature key pair failed\n");
    return ret;
  }
  ret = sgx_ecc256_close_context(ecc_handle);
  if(SGX_SUCCESS != ret){
    eprintf("[Err]: ecc256 context close failed\n");
    return ret;
  }

  return ret;
}

sgx_status_t e_decrypt(uint8_t* tk, uint32_t tk_size, uint8_t* ct, uint32_t ct_size, uint8_t* ct_mac){
  sgx_status_t ret = SGX_SUCCESS;

  return ret;
}

sgx_status_t e_projector(struct _pred_s p_pred, const char *s_in, char *s_out){
  sgx_status_t ret = SGX_SUCCESS;

  return ret;
}

sgx_status_t e_selector(struct _pred_s s_pred, const char *s_in, char *s_out){
  sgx_status_t ret = SGX_SUCCESS;

  return ret;
}

sgx_status_t e_aggregator(struct _pred_s a_pred, const char *s_in, char *s_out){
  sgx_status_t ret = SGX_SUCCESS;

  return ret;
}

sgx_status_t e_joiner(struct _pred_s j_pred, const char *s_in_1, const char *s_in_2, char *s_out){
  sgx_status_t ret = SGX_SUCCESS;

  return ret;
}
