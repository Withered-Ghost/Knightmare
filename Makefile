default:
	gcc engine.c init.c bitboards.c utils.c board.c -o engine

clean:
	rm ./*.exe
