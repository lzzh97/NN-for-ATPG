﻿sed -i 's/\r//g' script/all-fault-cases.sh
echo "NN-Hyb for all faults case without Lookup table"
echo -e "\n"

cd ./NN\_Hyb
echo "K=10000"
./atalanta -b 10000 -w ../circuits/c1908.bench
./atalanta -b 10000 -w ../circuits/c2670.bench
./atalanta -b 10000 -w ../circuits/c3540.bench
./atalanta -b 10000 -w ../circuits/c5315.bench
./atalanta -b 10000 -w ../circuits/c6288.bench
./atalanta -b 10000 -w ../circuits/c7552.bench
cd ..