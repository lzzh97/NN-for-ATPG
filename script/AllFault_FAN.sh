sed -i 's/\r//g' script/all-fault-cases.sh
echo "FAN for all faults case"
echo -e "\n"

echo "K=1000"
cd ./FAN
./atalanta -b 1000 ../circuits/c1908.bench
./atalanta -b 1000 ../circuits/c2670.bench
./atalanta -b 1000 ../circuits/c3540.bench
./atalanta -b 1000 ../circuits/c5315.bench
./atalanta -b 1000 ../circuits/c6288.bench
./atalanta -b 1000 ../circuits/c7552.bench

echo -e "\\n"
echo "K=10000"
./atalanta -b 10000 ../circuits/c1908.bench
./atalanta -b 10000 ../circuits/c2670.bench
./atalanta -b 10000 ../circuits/c3540.bench
./atalanta -b 10000 ../circuits/c5315.bench
./atalanta -b 10000 ../circuits/c6288.bench
./atalanta -b 10000 ../circuits/c7552.bench
echo -e "\\n"
echo "K=25000"
./atalanta -b 25000 ../circuits/c1908.bench
./atalanta -b 25000 ../circuits/c2670.bench
./atalanta -b 25000 ../circuits/c3540.bench
./atalanta -b 25000 ../circuits/c5315.bench
./atalanta -b 25000 ../circuits/c6288.bench
./atalanta -b 25000 ../circuits/c7552.bench

cd ..