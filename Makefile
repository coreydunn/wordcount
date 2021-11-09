all: wordcount
wordcount: main.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) wordcount
