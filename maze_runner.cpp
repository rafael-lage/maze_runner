#include <stdio.h>
#include <stack>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


//Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)

//funcao verifica se pos é valida
bool isValid(pos_t pos){
	if(pos.i >= 0 && pos.i < num_rows && pos.j >= 0 && pos.j < num_cols){
		return true;
	}
	else{
		return false;
	}
}

// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;

	// Abre o arquivo para leitura (fopen)
	FILE *file = fopen(file_name, "r"); // Abre o arquivo para leitura
    if (file == nullptr) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
    if (fscanf(file, "%d %d", &num_rows, &num_cols) != 2) {
        std::cerr << "Erro ao ler o número de linhas e colunas." << std::endl;
        fclose(file);
    }
    // Aloca as colunas para cada linha da matriz
    maze = new char *[num_rows];
		for (int i = 0; i < num_rows; i++) {
    maze[i] = new char[num_cols];
}
	char d = fgetc(file);
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			char c = fgetc(file);
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			maze[i][j] = c;
			// Se o valor for 'e' salvar o valor em initial_pos
			if(c == 'e'){
				initial_pos.i = i;
				initial_pos.j = j;
			}
			//printf("maze[%d][%d] = %c\n", i, j, maze[i][j]);
		}
		d = fgetc(file);
	}

    fclose(file);
	//printf("\nPrintando o labirinto\n");
	//print_maze();
	return initial_pos;
}


//funcao verifica se a posicao é valida
bool checkPos(pos_t pos){
	if(isValid(pos)){
		if(maze[pos.i][pos.j] == 'x' ){
			valid_positions.push(pos);
		}
		if(maze[pos.i][pos.j] == 's'){
			return(true);
		}
	}
	return(false);
}

// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool isFirst = true;
bool isEnd = false;
bool walk(pos_t pos) {
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
		//printf("isFirst = %d\n",isFirst);
	pos_t currentPos;
	if(isFirst){
		currentPos.i = pos.i;
		currentPos.j = pos.j;
		isFirst = false;
	}
	else if(!valid_positions.empty()){
		currentPos = valid_positions.top();
		valid_positions.pop();
	}
	maze[currentPos.i][currentPos.j] = '.';
	system("clear");
	print_maze();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	pos_t rightPos, leftPos, upPos,downPos;
	rightPos.i = currentPos.i;
	rightPos.j = currentPos.j+1;

	leftPos.i = currentPos.i;
	leftPos.j = currentPos.j-1;
	
	upPos.i = currentPos.i-1;
	upPos.j = currentPos.j;
	
	downPos.i = currentPos.i+1;
	downPos.j = currentPos.j;

	if(!isEnd) isEnd = checkPos(rightPos);
	if(!isEnd) isEnd = checkPos(leftPos);
	if(!isEnd) isEnd = checkPos(upPos);
	if(!isEnd) isEnd = checkPos(downPos);
	
	return (isEnd);
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/

		
	
		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso
		/*
		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
		}*/
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	//pos_t initial_pos = load_maze("../data/maze7.txt");
	pos_t initial_pos = load_maze(argv[1]);
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	while(!exit_found){
		exit_found = walk(initial_pos);
		if(!exit_found && valid_positions.empty()){
			printf("\nNao possui saida\n");
			return(0);
		}
	}
	

	for (int i = 0; i < num_rows; i++) {
    	delete[] maze[i];
	}
	delete[] maze;
	
	printf("\nSaida encontrada\n");
	
	// Tratar o retorno (imprimir mensagem)
	return 0;
}
