#include <stdio.h>
#include <stack>
#include <cstdlib>

// Matriz de char representnado o labirinto
char **maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

struct maze_infos{
	pos_t initial_pos;
	int rows;
	int cols;
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
maze_infos load_maze(const char* file_name) {
	
	pos_t initial_pos;
	FILE *file_maze;
	file_maze = fopen (file_name, "r");
	fscanf(file_maze, "%d %d\n", &num_rows, &num_cols);
	char c;

	maze = (char **) malloc(num_rows * sizeof(char*));

	// Abre o arquivo para leitura (fopen)
	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
	// Aloca a matriz maze (malloc)
	for (int i = 0; i < num_rows; i++){
		
		maze[i] = (char *) malloc(num_cols * sizeof(char*));	
	}
		// Aloca cada linha da matriz
	
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
			fscanf(file_maze, "%c", &maze[i][j]);
			if(maze[i][j] == 'e')
			{
				initial_pos.i = i;
				initial_pos.j = j;
			}
		}
		fscanf(file_maze, "%c", &c);
		}

	maze_infos infos;
	infos.initial_pos = initial_pos;
	infos.cols = num_cols;
	infos.rows = num_rows;

	return infos;
	};
// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
};


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
		
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

void walk(pos_t start, int rows, int cols) {
    valid_positions.push(start);

    while (!valid_positions.empty()) {
        pos_t current = valid_positions.top();
        valid_positions.pop();

        if (maze[current.i][current.j] == 's') {
            maze[current.i][current.j] = '.';
            print_maze();
            return;
        }

        maze[current.i][current.j] = '.';

        print_maze();
		printf("\n");


        if (current.i > 0 && maze[current.i-1][current.j] == 'x') {
            valid_positions.push({current.i-1, current.j});
        }
        if (current.i < rows-1 && maze[current.i+1][current.j] == 'x') {
            valid_positions.push({current.i+1, current.j});
        }
        if (current.j > 0 && maze[current.i][current.j-1] == 'x') {
            valid_positions.push({current.i, current.j-1});
        }
        if (current.j < cols-1 && maze[current.i][current.j+1] == 'x') {
            valid_positions.push({current.i, current.j+1});
        }
    }
};

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	maze_infos infos = load_maze("/workspaces/maze_runner/data/maze.txt");
	print_maze();
	walk(infos.initial_pos, infos.rows, infos.cols);
};
