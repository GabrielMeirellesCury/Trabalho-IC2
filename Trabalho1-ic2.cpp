#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <filesystem>

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
// inserção direta
void insercaoDireta(string ano[], int n) // n ta usando o ultimo do vetor pra ordenar
{
    string a[n + 1];
    for (int i = 0; i < n; i++)
    {
        a[i + 1] = ano[i];
    }

    string x;
    int j;

    for (int i = 2; i <= n; i++)
    {
        x = a[i];
        a[0] = x;
        j = i;
        while (x < a[j - 1])
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = x;
    }

    for (int i = 0; i < n; i++)
    {
        ano[i] = a[i + 1];
    }
}

// inserção binaria

void insercaoBin(string v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        string temp = v[i];
        int esq = 0, dir = i;

        while (esq < dir)
        {
            int m = (esq + dir) / 2;
            if (v[m] <= temp)
                esq = m + 1;
            else
                dir = m;
        }

        for (int j = i; j > esq; j--)
            v[j] = v[j - 1];

        v[esq] = temp;
    }
}

// seleção
void selecao(string ano[], int n)
{
    int indiceMenor;
    string x;

    for (int i = 0; i < n - 1; i++)
    {
        indiceMenor = i;
        for (int j = i + 1; j < n; j++)
        {
            if (ano[j] < ano[indiceMenor])
            {
                indiceMenor = j;
            }
        }
        x = ano[i];
        ano[i] = ano[indiceMenor];
        ano[indiceMenor] = x;
    }
}

// bubblesort
void bubble(string v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
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
    string x = ano[L];
    if (j < R && ano[j] < ano[j + 1])
    {
        j++;
    }
    while (j <= R && x < ano[j])
    {
        ano[i] = ano[j];
        i = j;
        j = 2 * i;
        if (j < R && ano[j] < ano[j + 1])
        {
            j++;
        }
    }
    ano[i] = x;
}

void heapsort(string ano[], int n) // ta copiando o primeiro valor no vetor inteiro
{
    string a[n + 1];
    for (int i = 0; i < n; i++)
    {
        a[i + 1] = ano[i];
    }

    string w;
    int L, R;

    for (L = n / 2; L >= 1; L--)
    {
        heapfy(a, L, n);
    }

    for (R = n; R >= 2; R--)
    {
        w = a[1];
        a[1] = a[R];
        a[R] = w;
        heapfy(a, 1, R - 1);
    }

    // passando o vetor ordenado a para ano
    for (int i = 0; i < n; i++)
    {
        ano[i] = a[i + 1];
    }
}

// fusao
void merge(string ano[], int L, int h, int R, string c[])
{
    int i = L;
    int j = h + 1;
    int k = L - 1;

    while (i <= h && j <= R)
    {
        k++;
        if (ano[i] < ano[j])
        {
            c[k] = ano[i];
            i++;
        }
        else
        {
            c[k] = ano[j];
            j++;
        }
    }
    while (i <= h)
    {
        k++;
        c[k] = ano[i];
        i++;
    }
    while (j <= R)
    {
        k++;
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
        for (j = i; j <= n; j++)
        {
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

    string x = v[(esq + dir) / 2];
    string w;

    do
    {
        while (v[i] < x)
            i++;

        while (v[j] > x)
            j--;

        if (i <= j)
        {
            w = v[i];
            v[i] = v[j];
            v[j] = w;
            i++;
            j--;
        }

    } while (i <= j);

    if (esq < j)
        quickSort(v, esq, j);

    if (i < dir)
        quickSort(v, i, dir);
}

//----------Busca binária----------

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
        insercaoDireta(ano_1, 100);
        insercaoDireta(ano_2, 500);
        insercaoDireta(ano_3, 1000);
        insercaoDireta(ano_4, 5000);
        insercaoDireta(ano_5, 10000);
        cout << "Ordenado com Insercao Direta!\n";
        break;
    case 2:
        insercaoBin(ano_1, 100);
        insercaoBin(ano_2, 500);
        insercaoBin(ano_3, 1000);
        insercaoBin(ano_4, 5000);
        insercaoBin(ano_5, 10000);
        cout << "Ordenado com Insercao Binaria!\n";
        break;
    case 3:
        selecao(ano_1, 100);
        selecao(ano_2, 500);
        selecao(ano_3, 1000);
        selecao(ano_4, 5000);
        selecao(ano_5, 10000);
        cout << "Ordenado com Selecao!\n";
        break;
    case 4:
        bubble(ano_1, 100);
        bubble(ano_2, 500);
        bubble(ano_3, 1000);
        bubble(ano_4, 5000);
        bubble(ano_5, 10000);
        cout << "Ordenado com BubbleSort!\n";
        break;
    case 5:
        heapsort(ano_1, 100);
        heapsort(ano_2, 500);
        heapsort(ano_3, 1000);
        heapsort(ano_4, 5000);
        heapsort(ano_5, 10000);
        cout << "Ordenado com HeapSort!\n";
        break;
    case 6:
        mergesort(ano_1, 100);
        mergesort(ano_2, 500);
        mergesort(ano_3, 1000);
        mergesort(ano_4, 5000);
        mergesort(ano_5, 10000);
        cout << "Fusao\n";
        break;
    case 7:
    {
        //ano1
        string a[101];
        for (int i = 0; i < 100; i++)//essa loucura toda aq é pq tem(? eu acho q sim) q deixar o 0 de sentinela no v[], mas ano n deixa o 0 de sentinela, ent tem q usar um outro e dps passar os valores desse outro pro ano
        {
            a[i + 1] = ano_1[i];
        }
        quickSort(a, 1, 100);
        for (int i = 0; i < 100; i++)
        {
            ano_1[i] = a[i + 1];
        }
        
        //ano2
        string b[501];
        for (int i = 0; i < 500; i++)
        {
            b[i + 1] = ano_2[i];
        }
        quickSort(b, 1, 500);
        for (int i = 0; i < 500; i++)
        {
            ano_2[i] = b[i + 1];
        }
        
        //ano3
        string c[1001];
        for (int i = 0; i < 1000; i++)
        {
            c[i + 1] = ano_3[i];
        }
        quickSort(c, 1, 1000);
        for (int i = 0; i < 1000; i++)
        {
            ano_3[i] = c[i + 1];
        }
        
        //ano3
        string d[5001];
        for (int i = 0; i < 5000; i++)
        {
            d[i + 1] = ano_4[i];
        }
        quickSort(d, 1, 5000);
        for (int i = 0; i < 5000; i++)
        {
            ano_4[i] = d[i + 1];
        }
        
        //ano5
        string e[10001];
        for (int i = 0; i < 10000; i++)
        {
            e[i + 1] = ano_5[i];
        }
        quickSort(e, 1, 10000);
        for (int i = 0; i < 10000; i++)
        {
            ano_5[i] = e[i + 1];
        }

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
    return 0;
}