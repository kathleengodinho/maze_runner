#include <chrono>
#include <thread>
#include <stdio.h>
#include <stack>
#include <cstdlib>

// Matriz de char representando o labirinto
char **maze;

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

void clear(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
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
// posições a serem exploradas no labirinto
std::stack<pos_t> valid_positions;

// Função que lê o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
maze_infos load_maze(const char* file_name) {
	pos_t initial_pos;
	FILE *file_maze;
	file_maze = fopen (file_name, "r");
	fscanf(file_maze, "%d %d\n", &num_rows, &num_cols);
	char c;

	maze = (char **) malloc(num_rows * sizeof(char*));
	
	for (int i = 0; i < num_rows; i++) {
		maze[i] = (char *) malloc(num_cols * sizeof(char));	
	}

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			fscanf(file_maze, "%c", &maze[i][j]);
			if(maze[i][j] == 'e') {
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

void print_solution(const std::stack<pos_t> &solution) {
    std::stack<pos_t> temp = solution;
    while (!temp.empty()) {
        pos_t p = temp.top();
        maze[p.i][p.j] = '.';
        temp.pop();
    }
    print_maze();
};


bool walk(pos_t start, int rows, int cols) {
    std::stack<pos_t> solution; // Armazena o caminho percorrido

    valid_positions.push(start);

    while (!valid_positions.empty()) {
        pos_t current = valid_positions.top();
        valid_positions.pop();

        if (maze[current.i][current.j] == 's') {
            solution.push(current);
            print_solution(solution);
            return true; // Encontrou a saída
        }

        if (maze[current.i][current.j] != 'e') {
            solution.push(current);
            clear(50);
            print_maze();
            printf("\n");
        }

        if (current.i > 0 && maze[current.i-1][current.j] == 'x') {
            maze[current.i-1][current.j] = '.';
            valid_positions.push({current.i-1, current.j});
        }
        if (current.i < rows-1 && maze[current.i+1][current.j] == 'x') {
            maze[current.i+1][current.j] = '.';
            valid_positions.push({current.i+1, current.j});
        }
        if (current.j > 0 && maze[current.i][current.j-1] == 'x') {
            maze[current.i][current.j-1] = '.';
            valid_positions.push({current.i, current.j-1});
        }
        if (current.j < cols-1 && maze[current.i][current.j+1] == 'x') {
            maze[current.i][current.j+1] = '.';
            valid_positions.push({current.i, current.j+1});
        }
    }

    return false; // Não encontrou a saída
}

int main(int argc, char* argv[]) {
    maze_infos infos = load_maze("/workspaces/maze_runner/data/maze.txt");
    print_maze();
    walk(infos.initial_pos, infos.rows, infos.cols);
}
