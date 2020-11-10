// labPrimKruskal.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <vector> 

#include "DHeap.cpp"
using namespace std;

int** generateGrapth(int n, float d, int upperBoundWeight, vector<vector<int>>&  edgesStore, int ** grapthMatrix, int** minOstMatrix)
{
    srand(time(0));
    int maxCountOfEdge = n * (n - 1) / 2;

    int countOfEdge = int(d * maxCountOfEdge);

    //int** grapthMatrix = new int* [n];
    //int** minOstMatrix = new int* [n];

    int count = n;

    int currentEdgeCount = 0;
    vector<int> vartFree;
    vector<int> vertBind;

    //vector<vector<int>> edgesStore;

   // for (int i = 0; i < n; i++) {
    //    grapthMatrix[i] = new int[n];
    //    minOstMatrix[i] = new int[n];
    //}

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                grapthMatrix[i][j] = -1;
                minOstMatrix[i][j] = -1;
            }
            else {
                grapthMatrix[i][j] = 0;
                minOstMatrix[i][j] = 0;
            }
        }
    }

    vertBind.push_back(0);
    for (int i = 1; i < n; i++) {
        vartFree.push_back(i);
    }

    while (count > 0 and vartFree.size() > 0) {
        int indexI = int(rand() % vartFree.size());
        int indexJ = int(rand() % vertBind.size());

        int i = vartFree[indexI];
        int j = vertBind[indexJ];

        if (grapthMatrix[i][j] == 0) {
            grapthMatrix[i][j] = 1;
            grapthMatrix[j][i] = 1;
            minOstMatrix[i][j] = minOstMatrix[j][i] = 1;
            //int tmp[3] = { i, j, 1 };
            edgesStore.push_back({ i, j, 1 });
            int tmpBind = vartFree[indexI];
            auto iter = vartFree.cbegin();
            vartFree.erase(iter + indexI);
            vertBind.push_back(tmpBind);
            currentEdgeCount++;
            count--;
        }
    }
         
    while (countOfEdge > currentEdgeCount) { 
        int i = int(rand() % n);
        int j = int(rand() % n);
        if (grapthMatrix[i][j] == 0) {

            int weight = int(rand() % upperBoundWeight) + 2;
            grapthMatrix[i][j] = weight;
            grapthMatrix[j][i] = weight;
            edgesStore.push_back({ i, j, weight });
            currentEdgeCount++;

        }
    }


    for (int i = 0; i < edgesStore.size(); i++) {
        int min = upperBoundWeight + 3;
        int minIndex = -1;
        for (int j = i; j < edgesStore.size(); j++) {
            if (edgesStore[j][2] <= min) {
                min = edgesStore[j][2];
                minIndex = j;
            }
        }
        swap(edgesStore[i], edgesStore[minIndex]);
    }

    cout << '\n';

    for (int i = 0; i < edgesStore.size(); i++) {
        cout << ' ' << edgesStore[i][2];
    }

    cout << '\n';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grapthMatrix[i][j]<<" ";
        }
        cout << '\n';
    }
    
    // return grapthMatrix, minOstMatrix;
    return grapthMatrix;
}

/*separated sets*/

void creation(int* p, int* r, int x)
{
    p[x] = x;
    r[x] = 0;
}

void join(int* p, int* r, int x, int y) {
    if (r[x] < r[y]) {
        p[x] = y;
    }
    else if (r[x] > r[y]) {
        p[y] = x;
    }
    else {
        p[x] = y;
        r[y] = r[y] + 1;
    }
}

int findRoot(int* p, int* r, int x) {
    int k = x;
    // first part
    while (p[x] != x) {
        x = p[x];
    }
    // second part
    while (p[k] != k) {
        int tmp = k;
        k = p[k];
        p[tmp] = x;
    }
    return x;
}

void mspKruskal(vector<vector<int>>& ET, vector<vector<int>>& E, int n) {
    int* p = new int[n];
    int* r = new int[n];
    int mt = 0;
    for (int i = 0; i < n; i++) {
        creation(p, r, i);
    }
    for (int i = 0; i < E.size(); i++) {
        cout << "E[i][0]" << " " << E[i][0] << "    " << "ET[i][1]" << " " << E[i][1]<<"\n";
        int a = findRoot(p, r, E[i][0]);
        int b = findRoot(p, r, E[i][1]);
        if (a != b) {
            join(p, r, a, b);
            ET.push_back(E[i]);
            //mt++;
        }
    }
    cout << "\n";
    cout << "ANSWER" << "\n";
    for (int i = 0; i < ET.size(); i++) {

        cout << ET[i][2] << " ";
    }
}

void mspPrim(int n, int** grapthMatrix) {
    vector<vector<DHeapItem>> grapth;
    grapth.reserve(n);
    for (int i = 0; i < n; i++) {
        vector<DHeapItem> tmpVector;
        for (int j = 0; j < n; j++) {
            // grapth.push_back({});
            if (grapthMatrix[i][j] > 0) {
                DHeapItem tmp(i, j, grapthMatrix[i][j]);
                tmpVector.push_back(tmp);
                
            }
        }
        if (tmpVector.size() > 0) {
            grapth.push_back(tmpVector);
        }
        else {
            grapth.push_back({});
        }
        
    }
    DHeap heap(3);
    int* used = new int[n];
    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }
    int u = 0;
    used[u] = 1;
    for (int i = 0; i < grapth[u].size(); i++) {
        //DHeapItem tmp(u, grapth[u][i].edgeSecond, grapth[u][i].weight);
       // cout << grapth[u][i].edgeFirst << " " << grapth[u][i].edgeSecond << " " << grapth[u][i].weight << " " << "\n";
        heap.push(u, grapth[u][i].edgeSecond, grapth[u][i].weight);
    }

    cout << "grapthsize " << grapth.size()<<" ";
    int mt = 0;
    while (mt<n-1)
    {
        DHeapItem tmp = heap.pop();
        u = tmp.edgeSecond;
        if (used[u] == 1) {
            continue;
        }
        int w = tmp.weight;
        mt++;
        cout << "\n";
        cout << tmp.edgeFirst<<" "<<tmp.edgeSecond << " " << tmp.weight << " "<<"\n";
        used[u] = 1;
        cout << "- " << u;
        for (int i = 0; i < grapth[u].size(); i++) {
            if (used[grapth[u][i].edgeSecond] != 1) {
                heap.push(u, grapth[u][i].edgeSecond, grapth[u][i].weight);
            }
            //DHeapItem tmp(u, grapth[u][i].edgeSecond, grapth[u][i].weight);
            
        }

    }

}

int main()
{
    vector<vector<int>> edgesStore;
    vector<vector<int>> ostEdgesStore;
    int N = 0;
    float d = 0.5;
    int UPPER = 0;
    cout << "Write V, d, upper bound of weight\n";
    cin >> N;
    cin >> d;
    cin >> UPPER;
    cout << "start generate grapth\n";
    //int** grapthMatrix = new int*[N];
    //int** minOstMatrix;
    int** grapthMatrix = new int* [N];
    int** minOstMatrix = new int* [N];

    //vector<vector<int>> edgesStore;

    for (int i = 0; i < N; i++) {
        grapthMatrix[i] = new int[N];
        minOstMatrix[i] = new int[N];
    }
    generateGrapth(N, d, UPPER, edgesStore, grapthMatrix, minOstMatrix);

    //** KRUSKAL

    mspKruskal(ostEdgesStore, edgesStore, N);

    //** PRIM

    /*vector<vector<DHeapItem>> grapth;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (grapthMatrix[i][j] > 0) {
                DHeapItem tmp(i, j, grapthMatrix[i][j]);
                grapth[i].push_back(tmp);
            }
        }
    }*/

    mspPrim(N, grapthMatrix);
    system("pause");
    return 0;

}

// d-heap


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
