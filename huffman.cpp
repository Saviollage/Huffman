#include <iostream>
#include <string>
#include <vector>

using namespace std;

class node
{
  public:
    int freq;
    string letter, code;
    node *left, *right;
};

bool verify(node nd, vector<node> &letterList) //verifica se o nó que ele recebe ja esta presente no vetor ou nao
{
    for (int i = 0; i < letterList.size(); i++)
        if (nd.letter == letterList.at(i).letter)
        {
            letterList.at(i).freq++;
            return false;
        }
    return true;
}

void showTree(node *a, int n) //mostra a arvore
{
    if (a)
    {
        int i;
        showTree(a->right, n + 1);
        for (i = 0; i < n; i++)
            cout << "\t";

        cout << " " << a->letter << endl;
        showTree(a->left, n + 1);
    }
}

void showVec(vector<node> letterList) //mostra o vetor
{
    for (int i = 0; i < letterList.size(); i++)
        cout << letterList.at(i).letter << ": " << letterList.at(i).freq << '\t';
}

void showCode(vector<node> letterList) //mostra o vetor
{
    for (int i = 0; i < letterList.size(); i++)
        cout << letterList.at(i).letter << ": " << letterList.at(i).code << '\n';
}

void organize(vector<node> &letterList) //ordena o vetor
{
    node aux;
    for (int i = 0; i < letterList.size(); i++)
        for (int j = 0; j < letterList.size(); j++)
            if (letterList.at(i).freq > letterList.at(j).freq)
            {
                aux = letterList.at(i);
                letterList.at(i) = letterList.at(j);
                letterList.at(j) = aux;
            }
}

void countFreq(string txt, vector<node> &letterList) //cria o vetor de frequencia
{
    node aux;

    for (int i = 0; i < txt.size(); i++) //percorre cada letra do texto
    {
        aux.letter = tolower(txt[i]); //aux recebe cada letra
        aux.freq = 0;                 //condiçoes iniciais
        aux.left = NULL;              //condiçoes iniciais
        aux.right = NULL;             //condiçoes iniciais

        if (verify(aux, letterList)) //se a letra nao extiste, ele a aloca no vetor
        {
            aux.freq++;
            letterList.push_back(aux);
        }
    }

    for (int i = 0; i < letterList.size(); i++) //só pra retirar o espaco em branco e colcoar algo visivel
    {
        if (letterList.at(i).letter == " ")
            letterList.at(i).letter = "[]";
    }

    organize(letterList); //ordena o vetor
}

node *buildHuffman(vector<node> letterList) //faz huffamn
{
    node *min1, *min2;
    node *root;
    node aux1, aux2;

    while (letterList.size() > 1) //faz essa verificação pq nosso codigo reduz o tamanho do vetor a cada laço
    {
        aux1 = letterList.at(letterList.size() - 1); //para receber os dois ultimos elementos do vetor
        aux2 = letterList.at(letterList.size() - 2);

        //criamos dois nós, min1 e min2 para aloca-los na arvore
        min1 = new node;
        min1->letter = aux1.letter;
        min1->freq = aux1.freq;
        min1->right = aux1.right;
        min1->left = aux1.left;

        min2 = new node;
        min2->letter = aux2.letter;
        min2->freq = aux2.freq;
        min2->right = aux2.right;
        min2->left = aux2.left;

        //cria o root, para ser formado pela junção dos dois menores valores do vetor
        root = new node;
        root->letter = min2->letter + min1->letter;
        root->freq = min2->freq + min1->freq;
        root->left = min2;
        root->right = min1;

        letterList.pop_back(); //remove os dois ultimos elementos, pois ja etao alocados na arvore
        letterList.pop_back();

        letterList.push_back(*root); //adiciona o elemento apos a juncao dos menores
        organize(letterList);        //ordena
    }

    return root;
}

void put(vector<node> &letterList, node root) //coloca o valor do codigo de cada letra da arvore no vetor
{
    for (int i = 0; i < letterList.size(); i++)
        if (letterList.at(i).letter == root.letter)
            letterList.at(i).code = root.code;
}

void coder(vector<node> &letterList, node *root)
{
    if (root->left != NULL || root->right != NULL) // nao é folha
    {
        root->right->code = root->code + "1"; //se anda pra direita, codigo recebe 1
        root->left->code = root->code + "0";  // se anda pra esquerda codigo recebe 0

        coder(letterList, root->left);
        coder(letterList, root->right);
    }

    put(letterList, *root); //preenche o vetor
}

void menu()
{
    cout << "\n\n#### HUFFMAN ####\n"
         << "\t1) Mostrar letras e frequencia\n"
         << "\t2) Mostrar arvore\n"
         << "\t3) Mostrar letras e seus códigos\n"
         << "\t4) Sair\n"
         << "Escolha uma opcao: ";
}

int main()
{
    string text = "O tempo perguntou pro tempo quanto tempo o tempo tem. O tempo respondeu pro tempo que o tempo tem tanto tempo quanto tempo o tempo tem";
    vector<node> letterList;
    node *root;
    int op = 1;

    countFreq(text, letterList);
    root = buildHuffman(letterList);
    coder(letterList, root);

    while (op > 0 && op < 4)
    {

        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            system("clear");
            showVec(letterList);
            break;
        case 2:
            system("clear");
            showTree(root, 0);
            break;
        case 3:
            system("clear");
            showCode(letterList);
            break;
        }
    }
}