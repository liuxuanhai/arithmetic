/**
 * C++ ÓïÑÔ: ¶ş²æ²éÕÒÊ÷
 *
 * @author skywang
 * @date 2013/11/07
 */

#include <iostream>
#include<stdlib.h>
#include "RBTree.h"
using namespace std;

int main()
{
    int i,x,y;
    RBTNode<int>* p;
    RBTree<int>* tree=new RBTree<int>();
    for(i=0; i<8; i++)
    {
        x = rand() % 100;
        y = rand() % 100;
        if(x > y) swap(x, y);
        tree->Inter_insert(new Interval<int>(x,y));
        cout<<"****************insert new member******"<<endl;
        tree->Inter_print();
    }
    /*cout<<"****************search the first overlap******"<<endl;
    cin>>x>>y;
    p=tree->Inter_search(new Interval<int>(x,y));
    if(p==NULL) cout<<"no exist"<<endl;
    else cout<<"the first is:["<<p->inter->low<<","<<p->inter->high<<"]"<<endl;*/
    cout<<"****************remove******"<<endl;
    cin>>x>>y;
    tree->Inter_remove(new Interval<int>(x,y));
    tree->Inter_print();


    // Ïú»ÙºìºÚÊ÷
    tree->destroy();

    return 0;
}
