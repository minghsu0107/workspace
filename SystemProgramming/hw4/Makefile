CFLAGS = -D_REENTRANT -Wall -pedantic -Isrc
LDLIBS = -lpthread

ifdef DEBUG
CFLAGS += -g
LDFLAGS += -g
endif

TARGETS = hw4 prepare_data bonus bonus_dynamic_link bonus_static_link \
	libthreadpool_dynamic.so libthreadpool_static.a

all: $(TARGETS)

hw4: src/hw4.c
	$(CC) -lm -lpthread -O3 -o $@ $<

prepare_data: src/prepare_data.c
	$(CC) -o $@ $<

src/bonus.o: src/bonus.c
	$(CC) -c -O3 -o $@ $< 
bonus: src/bonus.o libthreadpool.o
	$(CC) -lm -lpthread -o $@ $^

bonus_dynamic_link: src/bonus.o libthreadpool_dynamic.so
	$(CC) -o $@ $< -lm -L. -lthreadpool_dynamic 
bonus_static_link: src/bonus.o libthreadpool_static.a
	$(CC) -o $@ $< -lm -L. -lthreadpool_static -pthread

# Short-hand make aliases
shared: libthreadpool_dynamic.so
static: libthreadpool_static.a

libthreadpool_dynamic.so: libthreadpool.o src/threadpool.h
	$(CC) -shared -fPIC ${CFLAGS} -o $@ $< ${LDLIBS}

libthreadpool.o: src/threadpool.c src/threadpool.h
	$(CC) -w -c -O3 -fPIC ${CFLAGS} -o $@ $<

libthreadpool_static.a: libthreadpool.o
	ar rcs $@ $^

#-r 新增 .o 到 .a 中
#-c 建立新的程式庫
#-s 將一個 object 檔的 index 寫入程式庫

clean:
	rm -f $(TARGETS) *~ *.o */*.o
