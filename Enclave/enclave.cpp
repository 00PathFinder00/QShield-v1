#include <stdio.h>      /* vsnprintf */
#include <string.h>

#include "math.h"

#include "enclave_t.h"

void foo(char *buf, size_t len){
  const char *secret="Hello,World";
  if(len>strlen(secret)){
    memcpy(buf,secret,strlen(secret)+1);
  }
}
int enclaveAdd(int a,int b){
  return myadd(a,b);
}
