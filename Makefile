all:  
	gcc main.c src/menu.c src/Backtracking.c -o main 
production: 
	gcc main.c src/menu.c src/Backtracking.c   -D POSITION=$(position) -o main 
clean:  
	rm main