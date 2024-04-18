/**************************************************
*
* Daniel Arguello de Souza
* Trabalho de Estruturas de Dados
* Professor(a): Diego Rubert
*
*/

#include <cstdio> 
#include <cstddef>
#include <cstdint>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>

using std::vector;

/* Nó de uma árvore de Huffman */
class Node {
private:
  int f;     // Frequency
  uint8_t c; // Code
  Node *l;   // Left child
  Node *r;   // Right child
  
public:
  Node(int f, uint8_t c, Node *l = nullptr, Node *r = nullptr); // Construtor
  Node(int f = 0, Node *l = nullptr, Node *r = nullptr);        // Construtor
  int freq() const;     // Devolve a frequência do caractere
  uint8_t code() const; // Devolve o código do caractere
  Node *left();         // Devolve o filho esquerdo
  Node *right();        // Devolve o filho direito
  bool leaf() const;    // Devolve true se é folha e false caso contrário
};


/* Lista de min-prioridades (min-heap) com nós de uma árvore de
   Huffman, utilizando a frequência como chave */
class MinHeap {
private:
  vector<Node *> v;                                 // Elementos
  void up(unsigned int i);                          // Sobe
  void down(unsigned int i);                        // Desce
  unsigned int parent(unsigned int i);              // Pai
  unsigned int left(unsigned int i);                // Filho esquerdo
  unsigned int right(unsigned int i);               // Filho direito
  void troca(unsigned int i, unsigned int j);       //Troca - Daniel

public:
  MinHeap();            // Construtor padrão
  ~MinHeap();           // Destrutor padrão
  size_t size();        // Tamanho da heap
  void insert(Node *n); // Inserir elemento
  Node *extract();      // Remover (menor) elemento
};

int main(){
  //Entrada de arquivo do usuario
  std::string nome_arquivo;
  std::cout << "Digite o nome do arquivo que voce deseja compactar: ";
  std::getline(std::cin, nome_arquivo);

  std::ifstream arquivo(nome_arquivo);

  //Tratamento de erro
  if (!arquivo){
    std::cerr << "Houve um erro ao abrir o arquivo." << std::endl;
    return 1;
  }

  /* HashMap para armazenar os codigos ASCII 
  e frequencia dos caracteres */
  std::map<char, int> frequencias;

  //Frequencia dos Caracteres
  int caractere;
  while ((caractere = arquivo.get()) != EOF){
    char char_ascii = static_cast<char>(caractere);

    /* Verifica se char_ascii ja esta presente em frequencias,
    se nao estiver, adiciona o caractere e inicializa com    
    frequencia = 1. Caso ja esteja em frequencias, apenas
    incrementa o valor de sua frequencia em 1 */

    auto res = frequencias.find(char_ascii); 
    if (res != frequencias.end())
      frequencias[char_ascii]++; 
    else 
      frequencias[char_ascii] = 1;
  }


  return 0;
}

//Construtores Nó

int Node::freq() const{
  return f;
}

uint8_t Node::code() const{
  return c;
}

Node *Node::left(){
  return l;
}

Node *Node::right(){
  return r;
}

bool Node::leaf() const{
  //True - Folha; False - Não é Folha
  return (l == nullptr && r == nullptr);
}

//Construtores min_heap

unsigned int MinHeap::parent(unsigned int i) {
  return (i - 1) / 2;
}

unsigned int MinHeap::left(unsigned int i) {
  return 2 * (i + 1) - 1;
}

unsigned int MinHeap::right(unsigned int i) {
  return 2 * (i + 1);
}

void MinHeap::up(unsigned int i){
  while (v[parent(i)] < v[i]) {
    troca(i, parent(i));
    i = parent(i);
  }
}

void MinHeap::troca(unsigned int i, unsigned int j) {
  Node* aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

void MinHeap::down(unsigned int i){
  unsigned int e, d, maior;
  e = left(i);
  d = right(i);

  //Filho Esquerdo
  if (e < v.size() && v.at(e)->freq() > v.at(i)->freq())
    maior = e;
  else
    maior = i;

  //Filho Direito
  if (d < v.size() && v.at(d)->freq() > v.at(maior)->freq())
    maior = d;

  if (maior != i) {
    troca(i, maior);
    down(maior);
  }
}


