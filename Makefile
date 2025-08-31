default:
	gcc engine.c init.c bitboards.c -o engine

clean:
	rm ./*.exe
