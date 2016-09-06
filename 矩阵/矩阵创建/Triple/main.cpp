#include <iostream>
#include <fstream>
using namespace std;
template <class type>
class Triple
{
public:
    int row ;
    int col ;
    type val ;
} ;
template <class type>
class TripleMatrix
{
public :
    TripleMatrix(type ** source,int rows,int cols,type ignore) ;
    ~TripleMatrix() ;
    type ** transposeMatrix() ;
    void printTM() ;
private :
    Triple<type> * data ;
    int rows ;
    int cols ;
    int last ;
    type ignore ;
} ;
template <class type>
TripleMatrix<type>::TripleMatrix(type ** source,int rows,int cols,type ignore)
{
    this->rows = rows ;
    this->cols = cols ;
    this->last = 0 ;
    this->ignore = ignore ;
    int tmp[2][rows*cols] ;//缓存非零的行和列，提高效率
    for(int i = 0 ; i < rows ; i++)
    {
        for(int j = 0 ; j < cols ; j++)
        {
            if(source[i][j] != ignore)
            {
                tmp[0][last] = i ;
                tmp[1][last] = j ;
                last++ ;
            }
        }
    }
    data = new Triple<type>[last] ;
    for(int i = 0 ; i < last ; i++)
    {
        data[i].row = tmp[0][i] ;
        data[i].col = tmp[1][i] ;
        data[i].val = source[tmp[0][i]][tmp[1][i]] ;
    }
}
template <class type>
TripleMatrix<type>::~TripleMatrix()
{
    delete [] data ;
    data = NULL ;
}
template <class type>
type** TripleMatrix<type>::transposeMatrix()
{
    type ** TransMatrix ;
    TransMatrix = new type* [cols] ;
    for(int i = 0 ; i < cols ; i++)
    {
        TransMatrix[i] = new type [rows] ;
    }
    for(int i = 0 ; i < cols ; i++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            TransMatrix[i][j] = ignore ;
        }
    }
    for(int i = 0 ; i < last ; i++)
    {
        int row = data[i].col ;
        int col = data[i].row ;
        TransMatrix[row][col] = data[i].val ;
    }
    return TransMatrix ;
}
template <class type>
void TripleMatrix<type>::printTM()
{
    cout <<"\n三元组存储结构为:\n" ;
    cout <<"原矩阵共" <<rows<<"行"<<cols<<"列\n" ;
    cout <<"特殊元素:\n行数\t列数\t值\n" ;
    for(int i = 0 ; i < last ; i++)
    {
        cout <<data[i].row <<"\t" <<data[i].col<<"\t"<<data[i].val <<endl ;
    }
    cout <<"其余元素均为"<<ignore <<endl ;
}
int main()
{
    cout <<"请输入稀疏矩阵的行数和列数\n" ;
    int rows,cols ;
    cin >>rows >>cols ;
    cout <<"请输入矩阵的每个元素，按照从左到右，从上到下的顺序\n" ;
    int ** data ;
    data = new int*[rows] ;
    for(int i = 0 ; i < rows ; i++)
    {
        data[i] = new int[cols] ;
    }
    for(int i = 0 ; i< rows ; i++)
    {
        for(int j = 0 ; j < cols ; j++)
        {
            cin >> data[i][j] ;
        }
    }
    cout <<"输入完成\n" ;
    TripleMatrix<int> x(data,rows,cols,0) ;
    x.printTM() ;
    cout <<"其转置矩阵为\n" ;
    int ** trans = x.transposeMatrix() ;
    for(int i = 0 ; i < cols ; i++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            cout <<trans[i][j] <<" " ;
        }
        cout <<endl ;
    }
    //开始释放内存
    for(int i = 0 ; i < rows ; i++)
    {
        delete [] data[i] ;
        data[i] = NULL ;
    }
    delete [] data ;
    data = NULL ;
    for(int i = 0 ; i < cols ; i++)
    {
        delete [] trans[i] ;
        trans[i] = NULL ;
    }
    delete trans ;
    trans = NULL ;
    cout <<"按任意键结束\n" ;
    getchar() ;
    return 0;
}
