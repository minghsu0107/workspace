all: bidding_system host player

bidding_system: bidding_system.c my_header.h
	gcc bidding_system.c -o bidding_system
host: host.c my_header.h
	gcc host.c  -o host
player: player.c my_header.h
	gcc player.c  -o player

clean:
	rm -f bidding_system host player *.FIFO
