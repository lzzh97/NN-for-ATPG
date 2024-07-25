## File Structure

This repository includes the following directories and files:

- `README.md`: instructions to compile and generate results in the paper
- `NN-Hyb`: directory containing source code of our proposed approach
- `NN-All`: directory containing soruce code of alternative approach compared in the paper
- `circuits`: circuit files used in our experiments
- `hard_faults`: hard-to-detect faults per circuit used in results of Table II in the paper
- `script`: scripts to generate results in Tables I, II, III in the paper

## Installation

In the paper we have compared the following 3 approaches:

(1) Fan: base approach for ATPG used for comparison
(2) NN-Hyb: our approach based on applying our neural network (NN) model during backtrace at select levels of the circuit during ATPG
(3) NN-All: another alternative approach using our NN model, but at all levels of the circuit

To get an executable for (1), please download source code from https://github.com/hsluoyz/Atalanta and compile. (We did not include it because it is already published by another group.)

For (2) and (3), please compile (using the make command) from the NN-Hyb and NN-All directories, respectively.

## Options

Once compiled, use the command ./atalanta [path to circuit file] from each directory. The options needed to generate the results of the paper are listed below:

-w: Disable lookup table (enabled otherwise if -w not specified)

-b n: Maximum number of backtracking (default: -b 10)

-f fn: Faults are read from the file fn. This options is only used to generate the results in Table II in the paper. Otherwise, if a fault file is not specified, the input is assumed to be all possible faults.

## Run Experiments
The scripts in the "script" directory can be used to generate the results in the paper reported in Tables (1), (2) and (3). These are shown below for each case:

(1) Scripts for generating results in Table I: "All Faults Case":
- `AllFault_FAN.sh`
- `AllFault_NN-All.sh`
- `AllFault_NN-Hyb.sh`

Table I reports fault coverage, ATPG effectiveness, number of backtracks and runtime. These quantities are reported by our program for NN-All and NN-Hyb. 

For FAN's results, the tool does not directly report ATPG effectiveness. To compute it use this formula: (#redundant_faults + #detected_faults)/#total_faults 

(2) Scripts for generating results in Table II: "Hard-to-Detect Faults":
- `H2D_FAN.sh`
- `H2D_NN-Hyb.sh`

(3) Scripts for generating results in Table III: "Acceleration with Lookup Approach":
- `Acceleration_NN-Hyb.sh`

This script produces the results for NN-Hyb case, for both cases of with and without acceleration.
