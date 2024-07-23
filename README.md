# Automatic Test Pattern Generators (ATPG)

We provide three versions of automatic test pattern generators:

1. **FAN**: The original implementation of the FAN algorithm, serving as a benchmark ATPG algorithm.
2. **NN-Hyb**: Our NN-guided ATPG algorithm.
3. **NN-All**: ML model is applied to levels of a circuit.

## File Structure

This repository includes the following directories and files:

- `artifacts_submission`
  - `README`
  - `FAN`: The original implementation of FAN algorithm.
  - `NN-Hyb`: Our NN-guided ATPG algorithm.
  - `NN-All`: ML model is applied to levels of a circuit.
  - `circuits`: All the circuit files.
  - `hard_faults`: Hard-to-detect fault files.
  - `script`: Scripts to run our code.

## Installation

1. Navigate to the appropriate directory:
   - `./NN-Hyb` for the NN-guided ATPG algorithm.
   - `./FAN` for the FAN algorithm.
   - `./NN-All` for the NN-All algorithm.
2. Compile Atalanta using the `make` command to create the binary file `atalanta`.
3. Once compiled, run Atalanta under default settings using the command `./atalanta [path to circuit file]`.

## Options

- `-w`: Disable lookup table.
- `-b n`: The number of maximum backtrackings for the FAN algorithm phase 1. (default: -b 10)
- `-f fn`: Faults are read from the file fn. This option is available only for ISCAS89 netlist format. (default: faults are generated internally.)

## Run Experiments

To reproduce results for "all faults cases", use scripts:
- `AllFault_FAN.sh`
- `AllFault_NN-All.sh`
- `AllFault_NN-Hyb.sh`

The command should be like `bash script/AllFault_NN-Hyb.sh`. The outputs contain all results shown in Table I.

To reproduce results for "hard-to-detect faults", use scripts:
- `H2D_FAN.sh`
- `H2D_NN-Hyb.sh`

The command should be like `bash script/H2D_NN-Hyb.sh`. The outputs contain all results shown in Table II.

To reproduce results for NN-Hyb without acceleration, use the command `bash script/NoAcceleration_NN-Hyb.sh`. The outputs contain all results for NN-Hyb without lookup table shown in Table III.
