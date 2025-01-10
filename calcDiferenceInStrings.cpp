#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Funções de custo
int del_cost(char c) {
    return 1; // Custo de deleção
}

int ins_cost(char c) {
    return 1; // Custo de inserção
}

int sub_cost(char a, char b) {
    return (a == b) ? 0 : 2; // Custo de substituição (0 se igual, 2 se diferente)
}

// Função Min-Edit-Distance
int MinEditDistance(const string &source, const string &target) {
    int n = source.length();
    int m = target.length();

    // Criando a matriz de distâncias
    vector<vector<int>> D(n + 1, vector<int>(m + 1, 0));

    // Inicialização
    for (int i = 1; i <= n; ++i) {
        D[i][0] = D[i - 1][0] + del_cost(source[i - 1]);
    }
    for (int j = 1; j <= m; ++j) {
        D[0][j] = D[0][j - 1] + ins_cost(target[j - 1]);
    }

    // Relação de recorrência
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            D[i][j] = min({
                D[i - 1][j] + del_cost(source[i - 1]),          // Deleção
                D[i][j - 1] + ins_cost(target[j - 1]),          // Inserção
                D[i - 1][j - 1] + sub_cost(source[i - 1], target[j - 1]) // Substituição
            });
        }
    }

    // Retorno da distância mínima
    return D[n][m];
}

// Programa principal para teste
int main() {
    string source, target;
    cout << "Digite a string source: ";
    cin >> source;
    cout << "Digite a string target: ";
    cin >> target;

    int distance = MinEditDistance(source, target);
    cout << "A distância mínima de edição é: " << distance << endl;

    return 0;
}
