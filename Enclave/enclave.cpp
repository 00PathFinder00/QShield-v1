#include <stdio.h>      /* vsnprintf */
#include <string.h>
#include "enclave.h"
#include "enclave_t.h"


void foo(char *buf, size_t len){
  const char *secret="Hello,World";
  if(len>strlen(secret)){
    memcpy(buf,secret,strlen(secret)+1);

  }
}