echo "FAN for hard-to-detect faults case"
echo -e "\n"

cd ./FAN # cd to Atalanta source code from https://github.com/hsluoyz/Atalanta
echo "K=25000"
./atalanta -b 25000 -f ../hard_faults/c2670_h2d.ufaults ../circuits/c2670.bench
./atalanta -b 25000 -f ../hard_faults/c6288_h2d.ufaults ../circuits/c6288.bench
./atalanta -b 25000 -f ../hard_faults/c7552_h2d.ufaults ../circuits/c7552.bench

echo -e "\\n"
echo "K=50000"
./atalanta -b 50000 -f ../hard_faults/c2670_h2d.ufaults ../circuits/c2670.bench
./atalanta -b 50000 -f ../hard_faults/c6288_h2d.ufaults ../circuits/c6288.bench
./atalanta -b 50000 -f ../hard_faults/c7552_h2d.ufaults ../circuits/c7552.bench
cd ..
