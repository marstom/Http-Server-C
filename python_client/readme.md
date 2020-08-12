
# Measurements

### Method:
`time ./manyclinets.bash`

### Results
50 requests
1 thread backlog 1

./manyclinets.bash  8,41s user 0,96s system 235% cpu 3,978 total


change server backlog to 100

./manyclinets.bash  9,25s user 0,88s system 711% cpu 1,425 total
./manyclinets.bash  9,02s user 1,15s system 677% cpu 1,501 total
./manyclinets.bash  8,82s user 0,96s system 679% cpu 1,440 total

