# SP Homework 2

## Usage:
```shell=
make
./bidding_system [host_num] [player_num]
```

## Note:
It is worth noting that pipe and FIFO would block until the other end is read or written.
Therefore, we should make use of this attribute so that we always have data before moving on. Also, we cannot reposition the file pointer of FIFO or pipe.

Another important point is that as long as we write data smaller than PIPE_BUF, the action will be atomic. This guarantees that no interleaved data will be read.

In bidding_system.c, we save file pointers of all FIFO so that we can directly read or write to the file next time, saving the time for repopening. To comput final scores, I sort the indices of players by their scores, and iterate through the index array to find ranks.

In host.c, we only exec each host once; after finishing the current competion, each host will be blocked until players of the next competion are assigned. By the way, do not forget to redirect I/O before executing the processes!

Finally, always remember to wait for children! Otherwise, there will be resources leaked and zombie processes will be created.

## Test Resource Use
```shell=
time [command]
```