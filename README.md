# ipc_simple_example

## compile example
```
gcc -c utils.c -o utils.o -lm
gcc -c server.c -o server.o
gcc server.o utils.o -o server

gcc client.c -o client
```

## run
```
./server
```
```
./client
```