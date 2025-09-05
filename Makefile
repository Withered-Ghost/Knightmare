default:
	gcc engine.c init.c bitboards.c utils.c board.c data.c -o engine

clean:
	rm ./*.exe
