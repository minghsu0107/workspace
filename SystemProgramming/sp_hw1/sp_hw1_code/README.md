# Bank Server
## Usage
the command will generate read_server and write_server:
```
make
```
### For server side
To run write server:
```
./write_server [port]
```

To run read server:
```
./read_server [port]
```

### For client side:
```
telnet [host] [port]
```

## Explanation
For handling I/O multiplexing, I use select() to monitor every connected socket.
There are two possible situations.

The first is that the listening socket is ready for read. In other words, there is a new connection request from the remote client in the waiting queue. We should handle the new connection by accept(). accept() will return a new fd for the new connection.

The second situation is that the socket of the existe connection is ready for read. We should handle requests of the bank system here. I use check_read() and check_write() to handle the advisory lock for read requests and write requests respectively. We should ensure that an account waiting for write should not be read or written by other connections.
Finally, I use serve_write() to validate save, withdraw, and transfer operations. See more in **server.c**.
## Note
To compress/decompress a folder:
```
tar -zcvf compressed.tar.gz folder_name # compress
tar -xzvf compressed.tar.gz # decompress
```