# Automatic Test Pattern Generators

We provide two versions of automatic test pattern generators:

1. **Atalanta_fan**: The original implementation of the FAN algorithm, serving as a benchmark ATPG algorithm.
2. **Atalanta_nn**: Our NN-guided ATPG algorithm.

## File Structure

The repository includes the following directories and files:

- **artifacts_submission**
  - **README**: This document.
  - **FAN**: The original implementation of the FAN algorithm.
  - **NN-Hyb**: Our NN-guided ATPG algorithm.
  - **NN-All**: ML model applied to levels of a circuit.
  - **circuits**: All the circuit files.
  - **hard_faults**: Hard-to-detect fault files.
  - **script**: Scripts to run our code.

## Installation

1. Navigate to the appropriate directory:
   - `./NN-Hyb` for the NN-guided ATPG algorithm.
   - `./FAN` for the original FAN algorithm.
   - `./NN-All` for the NN-All algorithm.

2. Compile Atalanta using the `make` command to create the binary file `atalanta`:
   ```sh
   make
