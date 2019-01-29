

#include<iostream>
#include <list>
#include <stack>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#define NIL -1

using namespace std;


class Graph
{
    int V;
    int cc;
    vector<int> member;
    int* onWhichSCC;


    void dfs(int u, int disc[], int low[],
                 stack<int> *st, bool onStack[]);
public:
    Graph(int V);
    void createEdge(int v, int w);
    vector<int> findSCC();
    list<int> *adj;
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V+1];
    cc=0;
    onWhichSCC=new int[V+1];
    member.push_back(1);
}

void Graph::createEdge(int v, int w)
{
    adj[v].push_back(w);

}


void Graph::dfs(int u, int disc[], int low[], stack<int> *st,
                    bool onStack[])
{



    static int time = 0;


    disc[u] = low[u] = ++time;
    st->push(u);
    onStack[u] = true;


    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;


        if (disc[v] == -1)
        {
            dfs(v, disc, low, st, onStack);


            low[u]  = min(low[u], low[v]);
        }


        else if (onStack[v] == true)
            low[u]  = min(low[u], disc[v]);
    }


    int w = 0;
    if (low[u] == disc[u])
    {
        cc++;
        while (st->top() != u)
        {
            w = (int) st->top();
            onWhichSCC[w]=cc;
            onStack[w] = false;
            st->pop();
        }

        w = (int) st->top();
        member.push_back(w);
        onWhichSCC[w]=cc;
        onStack[w] = false;
        st->pop();
    }
}


vector<int> Graph::findSCC()
{
    int *disc = new int[V+1];
    int *low = new int[V+1];
    bool *onStack = new bool[V+1];
    stack<int> *st = new stack<int>();


    for (int i = 0; i <= V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        onStack[i] = false;
    }

    for (int i = 1; i <= V; i++) {
        if (disc[i] == NIL) {
            dfs(i, disc, low, st, onStack);
        }
    }

    bool isChild[cc+1];

    for(int i=1;i<=cc;i++)
        isChild[i]=false;

    for(int u=1;u<=V;u++) {

        for (int v:adj[u]) {

            if (onWhichSCC[u] != onWhichSCC[v]) {

                isChild[onWhichSCC[v]] = true;
            }
        }
    }

        vector<int> toCrack;

        for(int i=1;i<=cc;i++){

            if(!isChild[i]){

                toCrack.push_back(member[i]);

            }

        }



      return toCrack;

}

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    string line;
    vector<string> input;

    getline(infile, line);
    vector<string> word;
    split1(line, word);
    int V = stoi(word[0]);


    Graph graph(V);

    for(int i=1;i<=V;i++) {

        getline(infile, line);
        vector<string> words;
        split1(line, words);
        int nofKey=stoi(words[0]);
        for(int j=0;j<nofKey;j++){

            int key=stoi(words[j+1]);
            graph.createEdge(i, key);


        }

    }   /////GRAPH OLUŞTU

    ofstream myfile;
    myfile.open (argv[2]);

    vector<int> v=graph.findSCC();

    myfile << v.size() << " ";
   // cout << v.size() << " ";

    for (int k = 0; k < v.size(); ++k) {
        myfile << v[k] <<" ";
     //   cout << v[k] <<" ";
    }

    myfile.close();

    return 0;
}