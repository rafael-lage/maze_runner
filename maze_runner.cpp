#include <stdio.h>
#include <stack>
#include <iostream>
#include <cstdio>

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


// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;

	// Abre o arquivo para leitura (fopen)
		FILE *file = fopen("matriz.txt", "r"); // Abre o arquivo para leitura

    if (file == nullptr) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
    int num_rows, num_cols;
    if (fscanf(file, "%d %d", &num_rows, &num_cols) != 2) {
        std::cerr << "Erro ao ler o número de linhas e colunas." << std::endl;
        fclose(file);
        return 1;
    }

	// Aloca a matriz maze (malloc)
	**maze = (char **)malloc(num_rows * sizeof(char *)); // Aloca as linhas da matriz
	for (int i = 0; i < num_rows; ++i)
		maze[i] = (int *)malloc(num_cols * sizeof(int));
		// Aloca cada linha da matriz
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			char c = fgetc(file);
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			matriz[i+1][j] = c
			// Se o valor for 'e' salvar o valor em initial_pos
			if(c == 'e'){
				initial_pos.i = i+1;
				initial_pos.j = j;
			}
		}
	}
    fclose(file);
	return initial_pos;
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


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
	
	pos_t next_pos;

	//tenta andar para frente
	next_pos.i = pos.i;
	next_pos.j = pos.j + 1;

	maze[pos.i][pos.j] = '.';

	if(next_pos.i > 0 && next_pos.i < num_rows && next_pos.j > num_cols && maze[next_pos.i][next_pos.j] == 'x'){
		valid_positions.push(next_pos);
	}


	if(maze[pos.i][pos.j+1] == 'x')

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
		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
		}
	return false;
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze(argv[1]);
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	
	// Tratar o retorno (imprimir mensagem)
	
	return 0;
}
