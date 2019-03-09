include $(top_srcdir)/build-aux/sgx_tlib.am

lib_LIBRARIES = libsgx_tpbc.a

AUTOMAKE_OPTIONS = subdir-objects

ARITH_SOURCES = arith/field.c arith/z.c \
	arith/naivefp.c arith/fastfp.c \
	arith/fp.c arith/fasterfp.c arith/montfp.c \
	arith/ternary_extension_field.c \
	arith/multiz.c \
	arith/dlog.c \
	arith/fieldquadratic.c arith/poly.c \
	arith/random.c arith/init_random.c

ECC_SOURCES = ecc/mpc.c ecc/mnt.c ecc/hilbert.c ecc/curve.c ecc/pairing.c \
ecc/singular.c \
ecc/eta_T_3.c \
ecc/param.c ecc/a_param.c ecc/d_param.c ecc/e_param.c \
ecc/f_param.c ecc/g_param.c

MISC_SOURCES = misc/darray.c misc/symtab.c misc/get_time.c \
misc/utils.c misc/memory.c misc/extend_printf.c

libsgx_tpbc_a_CFLAGS = $(CFLAGS) -fno-builtin-memset -I$(top_srcdir)/include
libsgx_tpbc_a_SOURCES = $(ARITH_SOURCES) $(ECC_SOURCES) $(MISC_SOURCES)
