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

SUBDIRS = Enclave

## Supply additional flags to edger8r here.
##
## if SGX_WITH_SGXSDK
## SGX_EDGER8R_FLAGS=
## else
## OE_EDGER8R_FLAGS=
## endif


enclave.edl: Enclave/enclave.edl
	ln -s $?

## Needed to make our pattern rule work

AM_CPPFLAGS  += -fno-builtin-memset

## Additional automake variables
##
## AM_CPPFLAGS +=
## AM_CFLAGS =
## AM_CXXFLAGS =

bin_PROGRAMS = QShield

## the build target

enclave.signed.so: Enclave/enclave.signed.so
	ln -s $?

## copy the signed enclave to the current directory

QShield_SOURCES = Application/main.c
nodist_QShield_SOURCES = enclave_u.c enclave_u.h
BUILT_SOURCES = enclave_u.c enclave_u.h
EXTRA_QShield_DEPENDENCIES = enclave.signed.so

## You can't use $(wildcard ...) with automake so all source files
## have to be explicitly listed.

if SGX_WITH_SGXSDK
QShield_LDADD = -l$(SGX_URTS_LIB) -ldl -l:libsgx_capable.a -lpthread
else
QShield_LDADD = $(OE_APP_LIBS)
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
