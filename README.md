# QShield

A secure, efficient and scalable query framework for outsourcing data, which utilizes Intel SGX to protect the confidentiality and integrity of computations over sensitive data.

# Requirements

This project was built and tested with the following configuration:

* Ubuntu\* Linux\* 16.04
* CentOS\* Linux
* [Intel SGX SDK v2.0] (https://github.com/intel/linux-sgx)
* [SGX-enabled GMP library] (https://github.com/intel/sgx-gmp)
* [SGX-enabled PBC library]

# SGX-enabled PBC Library

We rewrite the pbc library to make it compatible with SGX development environment. The source code lies in QShield/tpl/pbc. Refer to following instructions to build the library.

* $cd QShield/tpl/pbc
* $./bootstrap
* $./configure prefix=<path of your SGX SDK directory> //e.g., /opt/sgxsdk
* $./make
* $./make install

Before you build the QShield project, please make sure that the libsgx_tgmp.a is also installed in SGX SDK directory.  

# Build

* $./bootstrap
* $./configure
* $./make

# Test

* $./QShield params/a.param
