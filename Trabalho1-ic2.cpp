#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//----------leiura de arquivos----------
void lerArquivo(fstream &arqAno, string ano[], int tamanho)
{
    if (!arqAno.is_open())
    {
        cout << "Arquivo não foi aberto corretamente";
        return;
    }

    string linhaLida;
    int i = 0;
    while (i < tamanho && getline(arqAno, linhaLida))
    {
        ano[i] = linhaLida;
        i++;
    }
}

//----------métodos de ordenação----------

// variáveis globais (da pra passar por ponteiro, preferem como? to com preguiça de fazer ponteiro)
int compDireta = 0;
int movDireta = 0;
int compBinaria = 0;
int movBinaria = 0;
int compSelecao = 0;
int movSelecao = 0;
int compBubble = 0;
int movBubble = 0;
int compHeap = 0;
int movHeap = 0;
int compMerge = 0;
int movMerge = 0;
int compQuick = 0;
int movQuick = 0;

// inserção direta
void insercaoDireta(string ano[], int n) // comp e mov bem diferente
{
    compDireta = 0;
    movDireta = 0;
    string a[n + 1];
    for (int i = 0; i < n; i++)
        a[i + 1] = ano[i];

    string x;
    int j;

    for (int i = 2; i <= n; i++)
    {
        compDireta++;

        x = a[i];
        a[0] = x;
        movDireta += 2;
        j = i;

        while (true)
        {
            compDireta++;
            if (!(x < a[j - 1]))
                break;
            a[j] = a[j - 1];
            movDireta++;
            j--;
        }

        a[j] = x;
        movDireta++;
    }

    for (int i = 0; i < n; i++)
        ano[i] = a[i + 1];
}

// inserção binaria

void insercaoBin(string v[], int n) // parece q ta sem sentinela, melhor fazer com. // ta com cerca de metade de mov e comp do q ta no drive, chat disse q ta perfeito
{
    compBinaria = 0;
    movBinaria = 0;
    compBinaria++;
    for (int i = 1; i < n; i++)
    {
        string temp = v[i];
        int esq = 0, dir = i;
        compBinaria++;
        while (esq < dir)
        {
            compBinaria++;
            int m = (esq + dir) / 2;
            compBinaria++;
            if (v[m] <= temp)
            {
                compBinaria++;
                esq = m + 1;
            }
            else
                dir = m;
        }
        compBinaria++;
        for (int j = i; j > esq; j--)
        {
            compBinaria++;
            movBinaria++;
            v[j] = v[j - 1];
        }
        movBinaria++;
        v[esq] = temp;
    }
}

/*versão do chat do algoritimo dele:
void insercaoBin(string v[], int n)
{
    // Criar array auxiliar com sentinela
    string a[n + 1];
    for (int i = 0; i < n; i++)
        a[i + 1] = v[i]; // copia v[0..n-1] para a[1..n]

    int L, R, j, m;
    string x;

    for (int i = 2; i <= n; i++)  // i = 2 até N
    {
        x = a[i];
        L = 1;
        R = i;

        while (L < R)  // busca binária
        {
            m = (L + R) / 2;
            if (a[m] <= x)
                L = m + 1;
            else
                R = m;
        }

        j = i;
        while (j > R)  // mover elementos
        {
            a[j] = a[j - 1];
            j--;
        }

        a[R] = x;  // inserir
    }

    // Copiar de volta para o vetor original
    for (int i = 0; i < n; i++)
        v[i] = a[i + 1];
}
*/

// seleção
void selecao(string ano[], int n) // mesmo com comp e mov nos mesmos lugares dos vets, ta bem diferente o mov e um pouco o comp. chat disse q ta certo
{
    compSelecao = 0;
    movSelecao = 0;
    int indiceMenor;
    string x;
    compSelecao++;
    for (int i = 0; i < n - 1; i++)
    {
        compSelecao++;
        indiceMenor = i;
        compSelecao++;
        for (int j = i + 1; j < n; j++)
        {
            compSelecao++; // do for
            compSelecao++; // do if
            if (ano[j] < ano[indiceMenor])
            {
                indiceMenor = j;
            }
        }
        movSelecao += 3;
        x = ano[i];
        ano[i] = ano[indiceMenor];
        ano[indiceMenor] = x;
    }
}

// bubblesort
void bubble(string v[], int n) // POUQUISSIMO A MAIS
{
    compBubble = 0;
    movBubble = 0;
    compBubble++;

    for (int i = 0; i < n - 1; i++)
    {
        compBubble++;
        compBubble++;

        for (int j = 0; j < n - i - 1; j++)
        {
            compBubble++;
            compBubble++;
            if (v[j] > v[j + 1])
            {
                movBubble += 3;
                string tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

// heapsort
void heapfy(string ano[], int L, int R)
{
    int i = L;
    int j = 2 * L;
    movHeap++;
    string x = ano[L];
    compHeap++;
    if (j < R && ano[j] < ano[j + 1])
    {
        compHeap++;
        j++;
    }
    compHeap++;
    while (j <= R && x < ano[j])
    {
        compHeap++;
        movHeap++;
        ano[i] = ano[j];
        i = j;
        j = 2 * i;
        compHeap++;
        if (j < R && ano[j] < ano[j + 1])
        {
            compHeap++;
            j++;
        }
    }
    movHeap++;
    ano[i] = x;
}

void heapsort(string ano[], int n)
{
    compHeap = 0;
    movHeap = 0;
    string a[n + 1];
    for (int i = 0; i < n; i++)
    {
        a[i + 1] = ano[i];
    }

    string w;
    int L, R;

    compHeap++;
    for (L = n / 2; L >= 1; L--)
    {
        compHeap++;
        heapfy(a, L, n);
    }

    compHeap++;
    for (R = n; R >= 2; R--)
    {
        compHeap++;
        movHeap++;
        w = a[1];
        a[1] = a[R];
        a[R] = w;
        movHeap += 2;
        heapfy(a, 1, R - 1);
    }

    for (int i = 0; i < n; i++)
    {
        ano[i] = a[i + 1];
    }
}

// fusao
void merge(string ano[], int L, int h, int R, string c[]) // comp BEM errado e mov perfeito
{
    movMerge = 0;
    int i = L;
    int j = h + 1;
    int k = L - 1;

    while (i <= h && j <= R)
    {
        k++;
        compMerge++;
        if (ano[i] < ano[j])
        {
            movMerge++;
            c[k] = ano[i];
            i++;
        }
        else
        {
            movMerge++;
            c[k] = ano[j];
            j++;
        }
    }
    while (i <= h)
    {
        k++;
        movMerge++;
        c[k] = ano[i];
        i++;
    }
    while (j <= R)
    {
        k++;
        movMerge++;
        c[k] = ano[j];
        j++;
    }
}

void mpass(string ano[], int n, int p, string c[])
{
    int i, j;
    i = 1;
    while (i <= n - 2 * p + 1)
    {
        merge(ano, i, i + p - 1, i + 2 * p - 1, c);
        i += 2 * p;
    }
    if (i + p - 1 < n)
    {
        merge(ano, i, i + p - 1, n, c);
    }
    else
    {
        compMerge++;
        for (j = i; j <= n; j++)
        {
            compMerge++; // assim? o dos vets ta estranha essa parte do codigo
            c[j] = ano[j];
        }
    }
}

void mergesort(string ano[], int n)
{
    string a[n + 1];
    for (int i = 0; i < n; i++)
    {
        a[i + 1] = ano[i];
    }
    compMerge = 0;

    string c[n + 1];
    int p = 1;
    while (p < n)
    {
        mpass(a, n, p, c);
        p *= 2;
        mpass(c, n, p, a);
        p *= 2;
    }
    // passando o vetor ordenado a para ano
    for (int i = 0; i < n; i++)
    {
        ano[i] = a[i + 1]; // necesário pq a está com a posição 0 vazia, mas o ano não
    }
}

// quicksort
/*
void quickSort(string v[], int esq, int dir) // ta completamente diferente doq ta no slide do tinos!!!! trocar pra versão dele
{
    if (esq < dir)
    {
        int p = esq, i = esq + 1, j = dir;
        while (i <= j)
        {
            if (v[i] > v[p])
                swap(v[i], v[j--]);
            else
                i++;
        }

        swap(v[p], v[j]);

        quickSort(v, esq, j - 1);
        quickSort(v, j + 1, dir);
    }
}*/

void quickSort(string v[], int esq, int dir)
{
    int i = esq;
    int j = dir;

    movQuick++;
    string x = v[(esq + dir) / 2];
    string w;

    do
    {
        compQuick++;
        while (v[i] < x)
        {
            compQuick++;
            i++;
        }

        compQuick++;
        while (v[j] > x)
        {
            compQuick++;
            j--;
        }

        compQuick++;
        if (i <= j)
        {
            compQuick++;
            movQuick += 3;
            w = v[i];
            v[i] = v[j];
            v[j] = w;
            i++;
            j--;
        }

    } while (i <= j);

    compQuick++;
    if (esq < j)
    {
        compQuick++;
        quickSort(v, esq, j);
    }

    compQuick++;
    if (i < dir)
    {
        compQuick++;
        quickSort(v, i, dir);
    }
}

//----------Busca binária----------

// Pedro --> busca binária (retorna índice ou -1)
int buscaBinaria(string v[], int n, const string &chave) {
    int esq = 0;
    int dir = n - 1;

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;

        if (v[meio] == chave)
            return meio;

        if (v[meio] < chave)
            esq = meio + 1;
        else
            dir = meio - 1;
    }

    return -1;
}

// Pedro --> lê um arquivo ordenado em um vetor fixo
bool carregarOrdenado(const string &nome, string v[], int tamanho) {
    ifstream arq(nome);
    if (!arq.is_open()) return false;

    string linha;
    int i = 0;

    while (getline(arq, linha) && i < tamanho) {
        if (linha != "")  // ignora linhas vazias
            v[i++] = linha;
    }

    arq.close();
    return true; // não exige tamanho exato
}


int main()
{

    fstream ano1, ano2, ano3, ano4, ano5;
    ano1.open("ano_1.txt", ios::in);
    ano2.open("ano_2.txt", ios::in);
    ano3.open("ano_3.txt", ios::in);
    ano4.open("ano_4.txt", ios::in);
    ano5.open("ano_5.txt", ios::in);

    string ano_1[100];
    string ano_2[500];
    string ano_3[1000];
    string ano_4[5000];
    string ano_5[10000];

    lerArquivo(ano1, ano_1, 100);
    lerArquivo(ano2, ano_2, 500);
    lerArquivo(ano3, ano_3, 1000);
    lerArquivo(ano4, ano_4, 5000);
    lerArquivo(ano5, ano_5, 10000);

    ano1.close();
    ano2.close();
    ano3.close();
    ano4.close();
    ano5.close();

    // ao inves de printar tudo para verificar, coloquei em arquivos
    ano1.open("ano_1_ord.txt", ios::out);
    ano2.open("ano_2_ord.txt", ios::out);
    ano3.open("ano_3_ord.txt", ios::out);
    ano4.open("ano_4_ord.txt", ios::out);
    ano5.open("ano_5_ord.txt", ios::out);

    int op;

    cout << "\nEscolha o método de ordenação" << endl;
    cout << "1 - Insercao Direta" << endl;
    cout << "2 - Insercao Binaria" << endl;
    cout << "3 - Selecao" << endl;
    cout << "4 - BubbleSort" << endl;
    cout << "5 - HeapSort" << endl;
    cout << "6 - Fusao" << endl;
    cout << "7 - QuickSort" << endl;
    cin >> op;

    switch (op)
    {
    case 1:
        cout << "Ordenado com Insercao Direta!\n";
        insercaoDireta(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compDireta << " Movimentacoes: " << movDireta << endl;
        insercaoDireta(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compDireta << " Movimentacoes: " << movDireta << endl;
        insercaoDireta(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compDireta << " Movimentacoes: " << movDireta << endl;
        insercaoDireta(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compDireta << " Movimentacoes: " << movDireta << endl;
        insercaoDireta(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compDireta << " Movimentacoes: " << movDireta << endl;
        break;
    case 2:
        cout << "Ordenado com Insercao Binaria!\n";
        insercaoBin(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compBinaria << " Movimentacoes: " << movBinaria << endl;
        insercaoBin(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compBinaria << " Movimentacoes: " << movBinaria << endl;
        insercaoBin(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compBinaria << " Movimentacoes: " << movBinaria << endl;
        insercaoBin(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compBinaria << " Movimentacoes: " << movBinaria << endl;
        insercaoBin(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compBinaria << " Movimentacoes: " << movBinaria << endl;
        break;
    case 3:
        cout << "Ordenado com Selecao!\n";
        selecao(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compSelecao << " Movimentacoes: " << movSelecao << endl;
        selecao(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compSelecao << " Movimentacoes: " << movSelecao << endl;
        selecao(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compSelecao << " Movimentacoes: " << movSelecao << endl;
        selecao(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compSelecao << " Movimentacoes: " << movSelecao << endl;
        selecao(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compSelecao << " Movimentacoes: " << movSelecao << endl;
        break;
    case 4:
        cout << "Ordenado com BubbleSort!\n";
        bubble(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compBubble << " Movimentacoes: " << movBubble << endl;
        bubble(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compBubble << " Movimentacoes: " << movBubble << endl;
        bubble(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compBubble << " Movimentacoes: " << movBubble << endl;
        bubble(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compBubble << " Movimentacoes: " << movBubble << endl;
        bubble(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compBubble << " Movimentacoes: " << movBubble << endl;
        break;
    case 5:
        cout << "Ordenado com HeapSort!\n";
        heapsort(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compHeap << " Movimentacoes: " << movHeap << endl;
        heapsort(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compHeap << " Movimentacoes: " << movHeap << endl;
        heapsort(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compHeap << " Movimentacoes: " << movHeap << endl;
        heapsort(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compHeap << " Movimentacoes: " << movHeap << endl;
        heapsort(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compHeap << " Movimentacoes: " << movHeap << endl;
        break;
    case 6:
        cout << "Fusao\n";
        mergesort(ano_1, 100);
        cout << "Ano 1: Comparacoes: " << compMerge << " Movimentacoes: " << movMerge << endl;
        mergesort(ano_2, 500);
        cout << "Ano 2: Comparacoes: " << compMerge << " Movimentacoes: " << movMerge << endl;
        mergesort(ano_3, 1000);
        cout << "Ano 3: Comparacoes: " << compMerge << " Movimentacoes: " << movMerge << endl;
        mergesort(ano_4, 5000);
        cout << "Ano 4: Comparacoes: " << compMerge << " Movimentacoes: " << movMerge << endl;
        mergesort(ano_5, 10000);
        cout << "Ano 5: Comparacoes: " << compMerge << " Movimentacoes: " << movMerge << endl;
        break;
    case 7:
    {
        // ano1
        string a[101];
        for (int i = 0; i < 100; i++) // essa loucura toda aq é pq tem(? eu acho q sim) q deixar o 0 de sentinela no v[], mas ano n deixa o 0 de sentinela, ent tem q usar um outro e dps passar os valores desse outro pro ano
        {
            a[i + 1] = ano_1[i];
        }
        compQuick = 0;
        movQuick = 0;
        quickSort(a, 1, 100);
        for (int i = 0; i < 100; i++)
        {
            ano_1[i] = a[i + 1];
        }
        cout << "Ano 1: Comparacoes: " << compQuick << " Movimentacoes: " << movQuick << endl;

        // ano2
        string b[501];
        for (int i = 0; i < 500; i++)
        {
            b[i + 1] = ano_2[i];
        }
        compQuick = 0;
        movQuick = 0;
        quickSort(b, 1, 500);
        for (int i = 0; i < 500; i++)
        {
            ano_2[i] = b[i + 1];
        }
        cout << "Ano 2: Comparacoes: " << compQuick << " Movimentacoes: " << movQuick << endl;

        // ano3
        string c[1001];
        for (int i = 0; i < 1000; i++)
        {
            c[i + 1] = ano_3[i];
        }
        compQuick = 0;
        movQuick = 0;
        quickSort(c, 1, 1000);
        for (int i = 0; i < 1000; i++)
        {
            ano_3[i] = c[i + 1];
        }
        cout << "Ano 3: Comparacoes: " << compQuick << " Movimentacoes: " << movQuick << endl;

        // ano4
        string d[5001];
        for (int i = 0; i < 5000; i++)
        {
            d[i + 1] = ano_4[i];
        }
        compQuick = 0;
        movQuick = 0;
        quickSort(d, 1, 5000);
        for (int i = 0; i < 5000; i++)
        {
            ano_4[i] = d[i + 1];
        }
        cout << "Ano 4: Comparacoes: " << compQuick << " Movimentacoes: " << movQuick << endl;

        // ano5
        string e[10001];
        for (int i = 0; i < 10000; i++)
        {
            e[i + 1] = ano_5[i];
        }
        compQuick = 0;
        movQuick = 0;
        quickSort(e, 1, 10000);
        for (int i = 0; i < 10000; i++)
        {
            ano_5[i] = e[i + 1];
        }
        cout << "Ano 5: Comparacoes: " << compQuick << " Movimentacoes: " << movQuick << endl;

        cout << "Ordenado com QuickSort!\n";
        break;
    }

    default:
        cout << "Opcao invalida!\n";
    }

    for (int i = 0; i < 100; i++)
    {
        ano1 << ano_1[i] << endl;
    }
    for (int i = 0; i < 500; i++)
    {
        ano2 << ano_2[i] << endl;
    }
    for (int i = 0; i < 1000; i++)
    {
        ano3 << ano_3[i] << endl;
    }
    for (int i = 0; i < 5000; i++)
    {
        ano4 << ano_4[i] << endl;
    }
    for (int i = 0; i < 10000; i++)
    {
        ano5 << ano_5[i] << endl;
    }

    ano1.close();
    ano2.close();
    ano3.close();
    ano4.close();
    ano5.close();

    // Pedro --> início do item 2 (cont. busca binária)
    cout << "\n\nItem 2: Busca Binária\n";

    string ord1[100], ord2[500], ord3[1000], ord4[5000], ord5[10000];

    bool ok1 = carregarOrdenado("ano_1_ord.txt", ord1, 100);
    bool ok2 = carregarOrdenado("ano_2_ord.txt", ord2, 500);
    bool ok3 = carregarOrdenado("ano_3_ord.txt", ord3, 1000);
    bool ok4 = carregarOrdenado("ano_4_ord.txt", ord4, 5000);
    bool ok5 = carregarOrdenado("ano_5_ord.txt", ord5, 10000);
    if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5) {
        cout << "Erro ao carregar arquivos ordenados. Execute primeiro o item 1.\n";
        return 0;
    }

    string codigo;
    cout << "\nDigite o código (10 letras) a ser pesquisado: ";
    cin >> codigo;
    bool encontrado = false;

    int pos;

    // ano 1
    pos = buscaBinaria(ord1, 100, codigo);
    if (pos != -1) {
        cout << "Encontrado no ANO 1, posição: " << pos << endl;
        encontrado = true;
    }

    // ano 2
    pos = buscaBinaria(ord2, 500, codigo);
    if (pos != -1) {
        cout << "Encontrado no ANO 2, posição: " << pos << endl;
        encontrado = true;
    }

    // ano 3
    pos = buscaBinaria(ord3, 1000, codigo);
    if (pos != -1) {
        cout << "Encontrado no ANO 3, posição: " << pos << endl;
        encontrado = true;
    }
    // ano 4
    pos = buscaBinaria(ord4, 5000, codigo);
    if (pos != -1) {
        cout << "Encontrado no ANO 4, posição: " << pos << endl;
        encontrado = true;
    }
    // ano 5
    pos = buscaBinaria(ord5, 10000, codigo);
    if (pos != -1) {
        cout << "Encontrado no ANO 5, posição: " << pos << endl;
        encontrado = true;
    }
    if (!encontrado) {
        cout << "Código NÃO encontrado em nenhum ano.\n";
    }
    
    cout << "\nFim do item 2!\n";

    return 0;
}
