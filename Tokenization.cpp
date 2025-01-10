#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Função para encontrar o par mais frequente no texto
pair<string, string> findMostFrequentPair(const vector<string>& tokens) {
    map<pair<string, string>, int> pairFrequency;

    // Contar frequência dos pares adjacentes
    for (size_t i = 0; i < tokens.size() - 1; ++i) {
        pair<string, string> pair = {tokens[i], tokens[i + 1]};
        pairFrequency[pair]++;
    }

    // Encontrar o par mais frequente
    pair<string, string> mostFrequent;
    int maxFreq = 0;
    for (const auto& entry : pairFrequency) {
        if (entry.second > maxFreq) {
            mostFrequent = entry.first;
            maxFreq = entry.second;
        }
    }

    return mostFrequent;
}

// Função para substituir um par por um token no texto
void mergePair(vector<string>& tokens, const pair<string, string>& toMerge) {
    vector<string> newTokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i < tokens.size() - 1 && tokens[i] == toMerge.first && tokens[i + 1] == toMerge.second) {
            // Substitui o par pelos tokens combinados
            newTokens.push_back(toMerge.first + toMerge.second);
            i++; // Pula o próximo token, pois já foi combinado
        } else {
            newTokens.push_back(tokens[i]);
        }
    }
    tokens = newTokens;
}

int main() {
    // Texto de entrada
    string text = "abababab";
    
    // Inicializar tokens (caracteres individuais)
    vector<string> tokens;
    for (char c : text) {
        tokens.push_back(string(1, c));
    }

    // Configuração do número máximo de iterações
    int maxMerges = 10;

    // Processamento do BPE
    for (int i = 0; i < maxMerges; ++i) {
        pair<string, string> mostFrequent = findMostFrequentPair(tokens);
        
        // Parar se não houver pares restantes
        if (mostFrequent.first.empty() && mostFrequent.second.empty()) break;

        cout << "Merge: " << mostFrequent.first << " " << mostFrequent.second << endl;

        mergePair(tokens, mostFrequent);

        // Exibir os tokens após cada passo
        cout << "Tokens: ";
        for (const string& token : tokens) {
            cout << token << " ";
        }
        cout << endl;
    }

    return 0;
}
