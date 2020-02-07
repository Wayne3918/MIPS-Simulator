# Yeet2 MIPS simulator

A C++ MIPS simulator to simulate the behaviour of MIPS assembly instructions. 

This simulator is built to fullfill the criteria of the Architecture II 2019 coursework at Imperial College London. It also contains a few testbenches for testing the CPU. 

This simulator is a pair coursework. Group partner's github page: https://github.com/UMust99

Coursework specification: https://github.com/m8pple/arch2-2019-cw

## To setup

The following command would compile and build the simulator: 

```bash
$ make simulator
```

The following command would compile and build the testbench: 

```bash
$ make testbench
```

A few MIPS assembly code files have been pre-installed in this repository. To run these, use the following command:

```bash
$ ./testbench bin/mips_simulator
```

## Result

Simulator raw marks : 95.45
Testbench raw marks : 80.39
