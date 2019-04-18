#ifndef E_SCHEME_H
#define E_SCHEME_H


#include "pbc/pbc.h"
#include "sgx_tcrypto.h"

#define SKBI_GTI_TAG_LEN 32
#define USER_NUM 10
typedef struct{
  element_t gti;
  sgx_sha256_hash_t skbi_tag;
}e_ska_compon;

typedef struct{
 element_t sk_a;
 pairing_t pairing;
 e_ska_compon comps[USER_NUM];
}e_ska;

typedef struct{
  element_t g;
  element_t m;
  element_t r;
  e_ska ska;
  element_t sk;
  element_t skb[USER_NUM];
}e_sk;

typedef struct{
  element_t c;
}cipher;


/**
core functions
*/

sgx_status_t epairinginit(pairing_t pairing, char* param, int count);
sgx_status_t ekeygen(e_sk *esk, char* param, int count);
// sgx_status_t eencrypt(uint8_t* msg, uint32_t msg_size, uint8_t *cipher, uint8_t *cipher_gcm_mac, element_t sk);
// sgx_status_t edecrypt(uint8_t* cipher, uint32_t cipher_size, uint8_t* msgs, uint8_t* msg_gcm_mac, char* policy, e_ska* ska, element_t skbi);

#endif//E_SCHEME_H
