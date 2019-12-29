#include <bits/stdc++.h>

using namespace std;


void mergeS(double a[], int s, int e, int p)
{
    double temp[1000];
    int k = 0;
    int i = s;
    int j = p + 1;
    while(i <= p && j <= e)
    {
        if(a[i] < a[j])
        {
            temp[k] = a[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            k++;
            j++;
        }
    }

    if(i > p)
    {
            while(j <= e)
            {
                temp[k] = a[j];
                j++;
                k++;
            }
    }
    else
    {
        while(i <= p)
        {
            temp[k] = a[i];
            i++;
            k++;
        }
    }
    for(int i = 0; i < k; i++)
    {
        a[i+s] = temp[i];
    }

}


void mergeSort(double a[], int i, int j)
{
    // divide
    int e = (int) (i + j) /2;
    if(i < e)
        mergeSort(a, i, e);
    if(e + 1 < j)
        mergeSort(a,e + 1, j);
    // conquer
    mergeS(a, i, j, e);
}


void output(double a[], int n)
{
    for(int i = 0; i < n; i++)
        cout << a[i];
    cout << endl;
}

struct node{
    double value;
    int index;
};

struct heap{
    vector<node> h;
    int sh;

    makeheap()
    {
        sh = h.size();
        int n = (h.size() - 1) / 2;
        for(int i = n; i > -1; i--)
            heapify(i);

    }

    heapify(int i)
    {
        int large = i;
        if(2*i + 1 < sh && h.at(large).value > h.at(2*i +1).value)
        {
            large = 2*i + 1;
        }
        if(2*i + 2 < sh && h.at(large).value > h.at(2*i + 2).value)
        {
            large = 2*i + 2;
        }
        if(large != i)
        {
            node temp = h.at(i);
            h.at(i) = h.at(large);
            h.at(large) = temp;
            heapify(large);
        }
    }

    void print()
    {
        for(int i = 0; i < sh; i++)
            cout << h.at(i).value << " ";
    }


};


void externalSort(string input, string output, int limit)
{
    vector<node> h;
    vector<string> namefile;
    double a[1000];
    fstream in;
    fstream out;
    in.open(input.c_str(), ios::in);
    out.open(output.c_str(), ios::out);
    fstream tempfile[1000];
    int k = 0;
    int i = 0;
    double temp = 0;
    node tmp;
    while(in>>temp)
    {

        a[i] = temp;
        i++;
        if(i == limit)
        {
            char buffer[20];
            sprintf(buffer, "file%d.txt", k);
            string tmpname(buffer);
            namefile.push_back(tmpname);
            tempfile[k].open(buffer, ios::out);
            mergeSort(a, 0, i - 1);
            for(int j = 0; j < i; j++)
                tempfile[k]<< setprecision(2) << fixed << a[j] << " ";
            i = 0;
            k++;
        }
    }
    char buffer[20];
    sprintf(buffer, "file%d.txt", k);
    string tmpname(buffer);
    namefile.push_back(tmpname);
    tempfile[k].open(buffer, ios::out);
    mergeSort(a, 0, i - 1);
    for(int j = 0; j < i; j++)
        tempfile[k]<<  setprecision(2) << fixed << a[j] << " ";
    k++;
    for(int i = 0; i < k; i++)
        tempfile[i].close();
    in.close();

    for(int i = 0; i < k; i++)
    {
        tempfile[i].open(namefile.at(i).c_str(), ios::in);
    }

    heap H;
    for( int i = 0;i < k; i++)
    {
        double number;
        tempfile[i] >> number;
        node tempnode;
        tempnode.value = number;
        tempnode.index = i;
        H.h.push_back(tempnode);
    }
    H.makeheap();

    // merge file
    int counter = 0;
    double value = 0;
    while(counter != k)
    {
        out << setprecision(2) << fixed << H.h.at(0).value << " ";
        if(!(tempfile[H.h.at(0).index] >> value))
        {
            value = INT_MAX;
            counter++;
        }
        tmp.value = value;
        tmp.index = H.h.at(0).index;
        H.h.at(0) = tmp;
        H.heapify(0);
    }
    for(int i = 0; i < k; i++)
        tempfile[i].close();
    out.close();
}


int main()
{
    string input = "number.txt";
    string output = "result.txt";
    externalSort(input, output, 5);
}
