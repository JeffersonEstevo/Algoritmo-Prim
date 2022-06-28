/* Implementação de Jefferson Estevo Feitosa
   Para a Disciplina Algortimos e Estruturas de Dados II
   DCA0209 - UFRN
*/

// STL implementação do algoritmo de Prim para MST
#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
 
// iPar ==> Par de inteiros
typedef pair<int, int> iPar;
 
// Essa classe representa um grafo usando uma
// representação por lista de adjacência 
class Grafo{
    int V;    // Nº de vértices
 
    // Em um grafo ponderado, precisamos armazenar o vértice
    // e par de pesos para cada aresta
    list< pair<int, int> > *adj;
 
public:
    Grafo(int V);  // Construtor
 
    // funcção para adicionar aresta no Grafo
    void addAresta(int u, int v, int w);
 
    // Imprimir a MST usando o algoritmo de Prim
    void primMST();
};
 
// Alocação de memória para a lista de adjacências
Grafo::Grafo(int V){
    this->V = V;
    adj = new list<iPar> [V];
}
 
void Grafo::addAresta(int u, int v, int w){
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
 
// Imprime caminhos mais curtos da raíz para todos os outros vértices
void Grafo::primMST(){
    // Cria uma fila de prioridade para armazenar vértices que estão sendo visitados 
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPar, vector <iPar> , greater<iPar> > pq;
 
    int raiz = 0; // Taking vertex 0 as source
 
    // Cria um vetor de chaves e inicializa todas as chave com infinito
    vector<int> chave(V, INF);

    // Armazena o vetor pai que, por sua vez, armazena MST
    vector<int> pai(V, -1);
 
    // Para acompanhar os vértices incluídos na MST
    vector<bool> pertence_a_MST(V, false);
    
    //Insere a raiz na fila de prioridade e inicializa su chave com 0
    pq.push(make_pair(0, raiz));
    chave[raiz] = 0;
 
    /* Laço até que a fila de prioridade fique vazia */
    while (!pq.empty()){
        
        // O primeiro vértice do par é a chave mínima
        // extrai este vértice da fila de prioridade
        // o rótulo do vértice é armazenado no segundo do par 
        // tem que ser feito desta forma para manter os vértices
        // chave ordenada (chave deve ser o primeiro item em pares)
        int u = pq.top().second;
        pq.pop();
         
          //Valores de chave diferentes para o mesmo vértice podem existir na fila de prioridade.
          //Aquele com o menor valor de chave é sempre processado primeiro.
          //Portanto, ignore o resto.
          if(pertence_a_MST[u] == true){
            continue;
        }
       
        pertence_a_MST[u] = true;  // Inclui o vértice na MST
 
        // 'i' é usado para obter todos os vértices adjacentes de um vértice
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            // Obtém o rótulo do vértice e o peso do adjacente atual de u
            int v = (*i).first;
            int peso = (*i).second;
 
            // Se v não estiver na MST e o peso de (u,v) for menor que a chave atual de v
            if (pertence_a_MST[v] == false && chave[v] > peso){
                // Updating key of v
                chave[v] = peso;
                pq.push(make_pair(chave[v], v));
                pai[v] = u;
            }
        }
    }
 
    // Imprime arestas da MST usando o array de pais
    for (int i = 1; i < V; ++i)
        printf("Conexão ==> %d - %d\n", pai[i], i);
}
 

int main(){
    // criar grafo
    int V = 8;
    Grafo g(V);
 
    // imprimir o grafo sendo construído  (vértice atual,vértice vizinho, peso)
    g.addAresta(0, 1, 4);
    g.addAresta(0, 4, 1);
    g.addAresta(0, 5, 2);
    g.addAresta(1, 2, 1);
    g.addAresta(1, 5, 1);
    g.addAresta(1, 6, 3);
    g.addAresta(2, 3, 2);
    g.addAresta(2, 6, 3);
    g.addAresta(3, 6, 1);
    g.addAresta(3, 7, 2);
    g.addAresta(3, 1, 4);
    g.addAresta(4, 5, 1);
    g.addAresta(5, 6, 3);
    g.addAresta(6, 7, 1);
    
    g.primMST();
    
    
    printf("\n***************************\n");
    int V2 = 4;
    Grafo g2(V2);
    
    g2.addAresta(0, 1, 1);
    g2.addAresta(0, 2, 2);
    g2.addAresta(1, 2, 5);
    g2.addAresta(1, 3, 3);
    g2.addAresta(2, 3, 4);
    
    g2.primMST();
    
    printf("\n***************************\n");
    int V3 = 10;
    Grafo g3(V3);
    
    g3.addAresta(0, 1, 6);
    g3.addAresta(0, 2, 1);
    g3.addAresta(0, 3, 14);
    g3.addAresta(1, 2, 10);
    g3.addAresta(1, 4, 6);
    g3.addAresta(1, 5, 8);
    g3.addAresta(2, 3, 7);
    g3.addAresta(2, 5, 7);
    g3.addAresta(3, 5, 6);
    g3.addAresta(3, 6, 6);
    g3.addAresta(4, 5, 4);
    g3.addAresta(4, 7, 3);
    g3.addAresta(5, 6, 1);
    g3.addAresta(5, 7, 6);
    g3.addAresta(5, 8, 5);
    g3.addAresta(6, 9, 5);
    g3.addAresta(7, 8, 6);
    g3.addAresta(8, 9, 5);
    
    g3.primMST();
    
    return 0;
}