## This must come first when building an application that uses Intel
## SGX enclaves. It can build against the Intel SGX SDK or Microsoft's
## OpenEnclave

include $(top_srcdir)/build-aux/sgx_app.am

## It adds a pattern rule for building proxy functions from EDL files:
##
##   %_u.h %_u.c: %.edl
##
## And sets the following automake and Makefile variables:
##
## ----- Intel SGX SDK ----------------------------------------------
##
##   SGXSDK
##   SGXSDK_BINDIR
##   SGXSDK_INCDIR
##   SGXSDK_LIBDIR
##   SGX_URTS_LIB
##   SGX_UAE_SERVICE_LIB
##   SGX_EDGER8R
##
##   AM_CPPFLAGS = -I$(SGXSDK_INCDIR)
##   AM_LDFLAGS = -L$(SGXSDK_LIBDIR)
##
## ----- OpenEnclave ------------------------------------------------
##
##   OE
##   OE_BINDIR
##   OE_INCDIR
##   OE_LIBDIR
##   OE_APP_LIBS
##   OE_EDGER8R
##
##   AM_CPPFLAGS = -I$(OE_INCDIR)
##   AM_LDFLAGS = -L$(OE_LIBDIR)
##
## ----- All --------------------------------------------------------
##
##   SGXSSL
##   SGXSSL_BINDIR
##   SGXSSL_INCDIR
##   SGXSSL_LIBDIR
##

AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = enc-src

## Supply additional flags to edger8r here.
##

enclave.edl: enc-src/enclave.edl
	ln -s $?

## Needed to make our pattern rule work

AM_CPPFLAGS  += -fno-builtin-memset -g -rdynamic

## Additional automake variables
##
## AM_CPPFLAGS +=
## AM_CFLAGS =
## AM_CXXFLAGS =

bin_PROGRAMS = QShieldEval

## the build target

enclave.signed.so: enc-src/enclave.signed.so
	ln -s $?

## copy the signed enclave to the current directory

QShieldEval_SOURCES = app-src/main.c app-src/naive_operators.c app-src/main.h app-src/naive_operators.h app-src/type.h
nodist_QShieldEval_SOURCES = enclave_u.c enclave_u.h
BUILT_SOURCES = enclave_u.c enclave_u.h
EXTRA_QShieldEval_DEPENDENCIES = enclave.signed.so

## You can't use $(wildcard ...) with automake so all source files
## have to be explicitly listed.

if SGX_WITH_SGXSDK
QShieldEval_LDADD = -l$(SGX_URTS_LIB) -ldl -l:libsgx_capable.a -lpthread
else
QShieldEval_LDADD = $(OE_APP_LIBS)
endif

## Library flags. At minimum, an Intel SGX SDK application will need:
##
##   -l$(SGX_URTS_LIB)
##
## Applications that use platform services or perform attestation
## will also need:
##
##  -l$(SGX_UA_SERVICE_LIB)
##
## Use the variables, not the actualy library names to ensure these
## targets work on simulation builds.
##
## OpenEnclave applications need, at minimum, $(OE_APP_LIBS)

CLEANFILES = enclave_u.c enclave_u.h enclave.edl \
  enclave_args.h enclave.signed.so

## Additional targets to remove with 'make clean'. You must list
## any edger8r generated files here.
