## This must come first when building an application that uses Intel
## SGX enclaves. It can build against the Intel SGX SDK or Microsoft's
## OpenEnclave

include $(top_srcdir)/build-aux/sgx_tlib.am

if SGX_WITH_SGXSDK
	AM_CPPFLAGS  += -fno-builtin-memset
endif


noinst_LIBRARIES = libe-scheme.a
libtpl_a_SOURCES = e-scheme.c e-scheme.h


CLEANFILES = $(noinst_LIBRARIES)
