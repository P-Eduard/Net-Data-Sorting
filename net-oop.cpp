#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;
#include "net-class.cpp"
char menu(int a=0)
{
    char op;
    if(a==1)cout<<endl<<endl;
    string menu="";
      menu+="0) Close.                        1) Print.";
    menu+="\n2) Add a node on a row.          3) Remove a node from a row.";
    menu+="\n4) Add a node on coordinates.    5) Remove node on coordinates.";
    menu+="\n6) Empty the net.                7) Count the nodes.";
    menu+="\n8) Swap nodes on coordinates.    9) Move node on coordinates.";
    menu+="\nq) Box the net.                  w) Sort the net.";
    menu+="\ne) Navigate the net.";
    menu+="\nOption: ";
    cout<<menu;
    cin>>op;
    return op;
}
int main()
{
    Net* head=new Net();
    head->first=NULL;
    char op=menu();
    int i;
    Node* current;
    while(1)
    switch(op)
    {
        default:
        {
            cout<<"Invalid.";
            op=menu(1);
            break;
        }
        case '0': //close
        {
            cout<<"The end.\n";
            return 0;
        }
        case '1': //print
        {
            head->printNet();
            op=menu(1);
            break;
        }
        case '2': //add node on row
        {
            int nr,rw;
            cout<<"Number: ";
            cin>>nr;
            cout<<"Row: ";
            cin>>rw;
            head->addRight(nr,rw,true);
            op=menu(1);
            break;
        }
        case '3': //remove node on row
        {
            cout<<"Row: ";
            cin>>i;
            head->delRight(i,true);
            op=menu(1);
            break;
        }
        case '4': //add node on coordinates
        {
            int nr,rw=9,cl=0;
            bool newRow=false;
            cout<<"Number: ";
            cin>>nr;
            while(rw!=0&&rw!=1)
            {
                cout<<"New row?\n0-no 1-yes: ";
                cin>>rw;
            }
            if(rw==1)newRow=true;
            if(newRow)
            {
                cout<<"Row: ";
                cin>>rw;
                head->addNode(nr,rw-1,cl,newRow,true);
                op=menu(1);
                break;
            }
            cout<<"Row: ";
            cin>>rw;
            cout<<"Column: ";
            cin>>cl;
            head->addNode(nr,rw,cl-1,newRow,true);
            op=menu(1);
            break;
        }
        case '5': //remove node on coordinates
        {
            int col,row;
            cout<<"Row: ";
            cin>>row;
            cout<<"Column: ";
            cin>>col;
            head->delNode(row,col,true);
            op=menu(1);
            break;
        }
        case '6': //empty the net
        {
            i=0;
            while(head->first!=NULL)
            {
                head->delRight(1,false);
                i++;
            }
            cout<<"Deleted "<<i<<" nodes.";
            op=menu(1);
            break;
        }
        case '7': //count nodes
        {
            i=head->countNodes(true);
            op=menu(1);
            break;
        }
        case '8': //swap node content on coordinates
        {
            int col1,col2,row1,row2;
            cout<<"row 1: ";
            cin>>row1;
            cout<<"column 1: ";
            cin>>col1;
            cout<<"row 2: ";
            cin>>row2;
            cout<<"column 2: ";
            cin>>col2;
            head->swapNode(row1,col1,row2,col2,true);
            op=menu(1);
            break;
        }
        case '9': //move node on coordinates
        {
            int row1,col1,row2,col2;
            cout<<"Row: ";
            cin>>row1;
            cout<<"Column: ";
            cin>>col1;
            cout<<"New row: ";
            cin>>row2;
            cout<<"New column: ";
            cin>>col2;
            col2--;
            head->moveNode(row1,col1,row2,col2,true);
            op=menu(1);
            break;
        }
        case 'e': //navigate
        {
            char nx='X';
            bool show=true;
            string spc,spc1;
            int mx;
            current=head->first;
            if(current==NULL)
            {
                cout<<"No net to navigate.";
                op=menu(1);
                break;
            }
            while(true)
            {
                if(nx=='Q')break;
                if(nx=='0')
                {
                    cout<<"\nThe end.\n";
                    return 0;
                }
                if(nx=='1')
                {
                    head->printNet();
                    cout<<endl;
                }
                else if(show)
                {
                    cout<<endl;
                    spc="    ";
                    if(current->left==NULL)spc+="  ";
                    else
                    if(current->left->nr<1000)spc+="  ";
                    else
                    {
                        mx=current->left->nr;
                        while(mx>0)
                        {
                            spc+=" ";
                            mx/=10;
                        }
                    }
                    cout<<spc;
                    if(current->up)cout<<current->up->nr<<endl<<spc<<"|"<<endl;
                    else cout<<"end"<<endl<<spc<<"|"<<endl;
                    if(current->left)
                    {
                        cout<<current->left->nr;
                        if(current->left->nr<10)cout<<"   - "<<current->nr<<"  - ";
                        else if(current->left->nr>10 && current->left->nr<100)cout<<"  - "<<current->nr<<"  - ";
                        else cout<<"  - "<<current->nr<<"  - ";
                    }
                    else cout<<"end"<<" - "<<current->nr<<" - ";
                    if(current->right)cout<<current->right->nr<<endl<<spc<<"|"<<endl;
                    else cout<<"end"<<endl<<spc<<"|"<<endl;
                    if(current->down)cout<<spc<<current->down->nr;
                    else cout<<spc<<"end";
                }
                spc1=spc;
                spc1.erase(spc1.length()-2);
                cout<<endl<<"Q W 0 1\n"<<"A S D\n"<<"Direction: ";
                cin>>nx;
                nx=toupper(nx);
                if(nx=='W')
                {
                    if(current->up!=NULL)
                    {
                        current=current->up;
                        show=true;
                    }
                    else
                    {
                        cout<<"Can't go up.\n";
                        show=false;
                    }
                }
                else if(nx=='S')
                {
                    if(current->down!=NULL)
                    {
                        current=current->down;
                        show=true;
                    }
                    else
                    {
                        cout<<"Can't go down.\n";
                        show=false;
                    }
                }
                else if(nx=='A')
                {
                    if(current->left!=NULL)
                    {
                        current=current->left;
                        show=true;
                    }
                    else
                    {
                        cout<<"Can't go left.\n";
                        show=false;
                    }
                }
                else if(nx=='D')
                {
                    if(current->right!=NULL)
                    {
                        current=current->right;
                        show=true;
                    }
                    else
                    {
                        cout<<"Can't go right.\n";
                        show=false;
                    }
                }
                else show=false;
            }
            op=menu(1);
            break;
        }
        case 'q': //box
        {
            head->boxNet(true);
            op=menu(1);
            break;
        }
        case 'w': //sort
        {
            head->sortNet(true);
            op=menu(1);
            break;
        }
    }
}
/*
a few imputs to check how the net behaves

nodes 1 2 3 on first 3 rows
2 1 1 2 2 1 2 3 1 2 1 2 2 2 2 2 3 2 2 1 3 2 2 3 2 3 3
2 1 1 2 2 1 2 3 1 2 1 2 2 2 2 2 1 3 2 2 3 2 3 3 1 4 4 0 2 2
2 1 1 2 2 1 2 3 1 2 1 2 2 2 2 2 3 2 2 1 3 2 2 3 2 3 3 2 5 2
2 1 1 2 2 1 2 3 1 2 1 2 2 2 2 2 3 2 2 1 3 2 2 3 2 3 3 9 3 1 1 3

2 nodes on 4 rows + 1
2 4 1 2 3 1 2 4 2 2 3 2 2 2 3 2 1 3 2 5 4 2 4 4 2 3 4

rows 2-3-2
2 1 1 2 1 1 2 1 2 2 1 2 2 1 3 2 1 3 2 1 2

row of 3, row of 4, row of 2
2 1 1 2 2 1 2 3 1 2 1 2 2 2 2 2 3 2 2 4 2 2 1 3 2 2 3

row of 5, row of 4
2 1 1 2 2 1 2 3 1 2 4 1 2 5 1 2 1 2 2 2 2 2 3 2 2 4 2

random rows with large numbers
2 666666 1 2 55555 1 2 7777777 2 2 4444 2 2 22 2 2 666666 3 2 88888888 3 2 666666 5 2 55555 5 2 7777777 6 2 4444 6 2 22 6 2 666666 7 2 88888888 7 2 333 2 2 22 2
*/
