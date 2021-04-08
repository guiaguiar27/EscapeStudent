all:  
	gcc main.c src/menu.c src/Backtracking.c -o main 
production: 
	gcc main.c src/menu.c src/Backtracking.c -o main 
clean:  
	rm main 