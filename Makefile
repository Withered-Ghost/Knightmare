default:
	gcc engine.c init.c bitboards.c utils.c board.c data.c attack.c -o engine

clean:
	rm ./*.exe
