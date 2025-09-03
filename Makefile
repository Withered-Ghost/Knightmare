default:
	gcc engine.c init.c bitboards.c utils.c -o engine

clean:
	rm ./*.exe
