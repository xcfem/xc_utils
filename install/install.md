xc_utils installation on Linux operating systems
================================================

## Precompiled packages
ATM there are no precompiled packages for no Linux distribution available. 
This means you need to compile XC yourself. This is quite straight forward 
with the documentation provided.

## Patience (please).
Please have patience. It takes some time and you may encounter some problems. 
If you have any problem at installation process, feel free to add an issue 
at <https://github.com/xcfem/xc_utils/issues>

## Introduction

### Installation steps
- install all needed depencies to be able to compile XC.
- get the source code (if not already done).
- compile the source code.
- install the libraries.
- verify the installation by running some verification tests.

## Install dependencies

### The short way
If you're using Debian strecht or Ubuntu 18 or 20 you can use scripts which
automate the installation of the packages needed. You will find further instructions in <https://github.com/xcfem/xc_utils/blob/master/install/install.scripts.linux.md>

### The not so short way
If you use a different Linux distribution you must install all packages needed for your distribution. See a detailed explanation here: <<https://github.com/xcfem/xc_utils/blob/master/install/dependencies_detailed_explanation.md>

## Get the source code

### Make a directory to place files inside:

```console
    mkdir prgs
    cd prgs
#
```
### Get the sources from git repository

```console
    git clone https://github.com/xcfem/xc_utils/ xc_utils
#
```

## Compile the source code

### Make a directory to compile sources.

```console
    mkdir ~/prgs/build
    mkdir ~/prgs/build/xc_utils
#
```


### Use CMake for Makefile generation.

```console
    cd ~/prgs/build/xc_utils
    cmake ../../xc_utils/src
#
```

### Compile code.

```console
    make
#
```
Or, if you have let's say 4 processors and 8 GB of RAM (or more) you can accelerate the process:

```console
    make -j 3
#
```

### Install libraries.

#### Install binary libraries.
To inform your system that there is some new libraries we need to make available system-wide you type:

```console
    sudo make install
#
```

You can verify that in the '/usr/local/lib' directory there is a file named 'libxc_utils.so'.

#### Install Python modules.


```console
    cd ~/prgs/xc_utils/python_modules
    sh local_install.sh
#
```

#### Run verification tests (test that all works as intended).


```console
    cd ~/prgs/xc_utils/verif
    chmod a+x run_verif.sh
	./run_verif.sh
#
```

