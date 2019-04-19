# QShield

A secure, efficient and scalable query framework for outsourcing data, which utilizes Intel SGX to protect the confidentiality and integrity of computations over sensitive data.

# Requirements

This project was built and tested with the following configuration:

* Ubuntu\* Linux\* 16.04
* CentOS\* Linux
* [Intel SGX SDK v2.0] (https://github.com/intel/linux-sgx)
* [SGX-enabled GMP library] (https://github.com/intel/sgx-gmp)
* [SGX-enabled PBC library]
* [E-Scheme]

# SGX-enabled PBC Library

We rewrite the pbc library to make it compatible with SGX development environment. The source code lies in QShield/tpl/pbc. Refer to following instructions to build the library.

* $cd QShield/tpl/pbc
* $./bootstrap
* $./configure prefix=<path of SGX SDK directory> //e.g., /opt/sgxsdk
* $./make
* $./make install

Before you build the QShield project, please make sure that the libsgx_tgmp.a is also installed in SGX SDK directory. (You may just copy QShield/tpl/gmp/sgx_tgmp.h -> <path of SGX SDK directory>/include; QShield/tpl/gmp/libsgx_tgmp.a -> <path of SGX SDK directory>/lib64) 

# E-Scheme

We design a E-Sheme to facilitate key management, data encryption/decryption, and access control enforcement.

* $cd QShield/tpl/e-scheme
* $cp e-scheme.h <path of SGX SDK directory>/include/escheme/
* $cp libsgx_tescheme.a <path of SGX SDK directory>/lib64/

# Build

* $./bootstrap
* $./configure [--enable-sgx-simulation]
* $./make

# Test

* $./QShield params/a.param

At present, QShield supports four operators, i.e., selector, projector, joiner, and aggregator[SUM]. This prototype illustrates a sample query plan (S0 -> S1 -> S2; S0 -> S3; S2 & S3 -> S4 -> S5).
