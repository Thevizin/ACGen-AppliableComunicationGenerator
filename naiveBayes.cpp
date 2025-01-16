#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// Função para tokenizar um documento em palavras
vector<string> tokenize(const string& doc) {
    vector<string> tokens;
    string word;
    for (char ch : doc) {
        if (isalpha(ch)) {
            word += tolower(ch);
        } else if (!word.empty()) {
            tokens.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) tokens.push_back(word);
    return tokens;
}

// Função para treinar o Naive Bayes
void trainNaiveBayes(
    const vector<pair<string, string>>& D, // Dados (documento, classe)
    unordered_set<string>& V, // Vocabulário
    unordered_map<string, double>& logprior, // Log P(c)
    unordered_map<string, unordered_map<string, double>>& loglikelihood // Log P(w|c)
) {
    unordered_map<string, int> classDocCount; // Número de documentos por classe
    unordered_map<string, unordered_map<string, int>> wordCount; // Contagem de palavras por classe
    unordered_map<string, int> totalWordCount; // Total de palavras por classe
    int Ndoc = D.size(); // Número total de documentos

    // Construir o vocabulário e coletar contagens
    for (const auto& [doc, cls] : D) {
        classDocCount[cls]++;
        vector<string> tokens = tokenize(doc);
        for (const string& word : tokens) {
            V.insert(word);
            wordCount[cls][word]++;
            totalWordCount[cls]++;
        }
    }

    // Calcular logprior
    for (const auto& [cls, count] : classDocCount) {
        logprior[cls] = log((double)count / Ndoc);
    }

    // Calcular loglikelihood com suavização de Laplace
    int vocabSize = V.size();
    for (const auto& [cls, words] : wordCount) {
        for (const string& word : V) {
            int wordFreq = words.count(word) ? words.at(word) : 0;
            loglikelihood[cls][word] = log((wordFreq + 1.0) / (totalWordCount[cls] + vocabSize));
        }
    }
}

// Função para testar o Naive Bayes
string testNaiveBayes(
    const string& testdoc,
    const unordered_set<string>& V,
    const unordered_map<string, double>& logprior,
    const unordered_map<string, unordered_map<string, double>>& loglikelihood
) {
    unordered_map<string, double> sum; // Soma para cada classe
    for (const auto& [cls, prior] : logprior) {
        sum[cls] = prior;
        vector<string> tokens = tokenize(testdoc);
        for (const string& word : tokens) {
            if (V.count(word)) {
                sum[cls] += loglikelihood.at(cls).count(word) ? loglikelihood.at(cls).at(word) : 0;
            }
        }
    }

    // Retornar a classe com maior soma
    return max_element(sum.begin(), sum.end(),
        [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second < b.second;
        })->first;
}

int main() {
    // Dados de treinamento: (documento, classe)
    vector<pair<string, string>> trainingData = {
        {"Eu amo programação", "positivo"},
        {"Eu odeio bugs", "negativo"},
        {"A programação é incrível", "positivo"},
        {"Corrigir bugs é chato", "negativo"}
    };

    // Inicializar estruturas
    unordered_set<string> V; // Vocabulário
    unordered_map<string, double> logprior; // Log P(c)
    unordered_map<string, unordered_map<string, double>> loglikelihood; // Log P(w|c)

    // Treinar o modelo
    trainNaiveBayes(trainingData, V, logprior, loglikelihood);

    // Testar um documento
    string testDoc = "Eu odeio programação";
    string predictedClass = testNaiveBayes(testDoc, V, logprior, loglikelihood);

    cout << "Classe prevista: " << predictedClass << endl;

    return 0;
}