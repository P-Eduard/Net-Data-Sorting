class Node
{
    public:
        int nr;
        Node* left;
        Node* right;
        Node* up;
        Node* down;
};
class Net
{
    public:
        Node* first;
        int maxNr;
        void printNet();
        int findMax(bool msg);
        int countNodes(bool msg);
        void addRight(int wnr,int row, bool msg);
        void delRight(int row, bool msg);
        void addNode(int wnr, int row, int col, bool newRow, bool msg);
        void delNode(int row, int col, bool msg);
        void swapNode(int row1, int col1, int row2, int col2, bool msg);
        void moveNode(int row1, int col1, int row2, int col2, bool msg);
        void boxNet(bool msg);
        void sortNet(bool msg);
};
void Net::printNet()
{
    cout<<endl;
    int spc=to_string(this->maxNr).length();
    if(spc==1)spc+=2;
    else if(spc==2)spc+=1;
    if(this->first==NULL)
    {
        cout<<"Empty.";
        return;
    }
    Node* current=this->first;
    int a, b=0;
    while(current!=NULL)
    {
        int printNum=0,a,b1=b;
        Node* currentrow=current;
        if(currentrow==NULL)
        {
            cout<<"end";
            b=0;
        }
        else
        {
            string vRow="";
            while(currentrow!=NULL)
            {
                cout<<currentrow->nr<<" > ";
                printNum++;
                vRow+="v   ";
                a=spc-to_string(currentrow->nr).length();
                while(a>0)
                {
                    cout<<" ";
                    a--;
                }
                a=spc-1;
                while(a>0)
                {
                    vRow+=" ";
                    a--;
                }
                currentrow=currentrow->right;
            }
            b1=b1-printNum-1;
            cout<<"end";
            while(b1>0)
            {
                a=spc;
                while(a>0)
                {
                    cout<<" ";
                    a--;
                }
                cout<<"end";
                b1--;
            }
            cout<<endl<<vRow<<endl;
            b=printNum;
            current=current->down;
        }
    }
    cout<<"end";
    b--;
    while(b>0)
    {
        a=spc;
        while(a>0)
        {
            cout<<" ";
            a--;
        }
        cout<<"end";
        b--;
    }
}
int Net::findMax(bool msg)
{
    if(this->first==NULL) return 0;
    int m=this->first->nr;
    Node *current=this->first;
    while(current!=NULL)
    {
        Node *currentrow=current;
        while(currentrow!=NULL)
        {
            if(currentrow->nr>m)m=currentrow->nr;
            currentrow=currentrow->right;
        }
        current=current->down;
    }
    if(msg)cout<<"The biggest number is "<<m<<".";
    return m;
}
int Net::countNodes(bool msg)
{
    Node *current1=this->first, *current2;
    int i=0;
    while(current1!=NULL)
    {
        for(current2=current1; current2!=NULL; current2=current2->right)i++;
        current1=current1->down;
    }
    if(msg)cout<<"There are "<<i<<" nodes.";
    return i;
}
void Net::addRight(int wnr,int row,bool msg)
{
    Node *current=this->first, *newNode=new Node;
    newNode->nr=wnr;
    newNode->up=NULL;
    newNode->down=NULL;
    newNode->left=NULL;
    newNode->right=NULL;
    if(current==NULL)
    {
        this->first=newNode;
        this->maxNr=newNode->nr;
        if(msg)cout<<"Added "<<wnr<<" head. ";
        return;
    }
    int i=1;
    while(i<row)
    {
        if(current->down==NULL)
        {
            current->down=newNode;
            newNode->up=current;
            if(this->maxNr<newNode->nr)this->maxNr=newNode->nr;
            if(msg)cout<<"Added "<<wnr<<" new row. ";
            return;
        }
        current=current->down;
        i++;
    }
    while(current->right!=NULL)current=current->right;
    current->right=newNode;
    newNode->left=current;
    if(current->up!=NULL && current->up->right!=NULL)
    {
        newNode->up=current->up->right;
        newNode->up->down=newNode;
    }
    if(current->down!=NULL && current->down->right!=NULL)
    {
        newNode->down=current->down->right;
        newNode->down->up=newNode;
    }
    if(this->maxNr<newNode->nr)this->maxNr=newNode->nr;
    if(msg)cout<<"Added "<<wnr<<" middle. ";
    return;
}
void Net::delRight(int row, bool msg)
{
    Node *current=this->first, *aux;
    int del;
    if(current==NULL)
    {
        if(msg)cout<<"Delete Right: Nothing to remove.\n";
        return;
    }
    int i=1;
    while(i<row)
    {
        if(current->down==NULL)
        {
            cout<<"Delete Right: Couldn't find the node.\n";
            return;
        }
        current=current->down;
        i++;
    }
    while(current->right!=NULL)current=current->right;
    del=current->nr;
    if(i==1 && current->left==NULL)
    {
        this->first=current->down;
        if(current->down!=NULL)current->down->up=NULL;
        free(current);
        this->maxNr=this->findMax(false);
        if(msg)cout<<"Removed "<<del<<".";
        return;
    }
    if(current->left==NULL)
    {
        if(current->up!=NULL)current->up->down=current->down;
        if(current->down!=NULL)
        {
            current->down->up=current->up;
            aux=current;
            if(aux->up!=NULL)
            {
                aux=aux->up->right;
                while(aux!=NULL)
                {
                    if(aux->left->down->right==NULL || aux->left->down==NULL) break;
                    aux->down=aux->left->down->right;
                    aux->down->up=aux;
                    aux=aux->right;
                }
            }
            else if(aux->down!=NULL)
            {
                aux=aux->down->right;
                while(aux!=NULL)
                {
                    if(aux->left->up->right==NULL)break;
                    aux->up=aux->left->up->right;
                    aux->up->down=aux;
                    aux=aux->right;
                }
            }
        }
    }
    else
    {
        if(current->up!=NULL)current->up->down=NULL;
        if(current->down!=NULL)current->down->up=NULL;
        current->left->right=NULL;
    }
    free(current);
    this->maxNr=this->findMax(false);
    if(msg)cout<<"Removed "<<del<<".";
    return;
}
void Net::addNode(int wnr, int row, int col, bool newRow, bool msg)
{
    Node *current=this->first, *newNode=new Node, *aux;
    newNode->nr=wnr;
    newNode->up=NULL;
    newNode->down=NULL;
    newNode->left=NULL;
    newNode->right=NULL;
    if(current==NULL)
    {
        this->first=newNode;
        this->maxNr=newNode->nr;
        if(msg)cout<<"Added "<<wnr<<" head. ";
        return;
    }
    int i=1;
    if(newRow)
    {
        if(row==0)
        {
            newNode->down=this->first;
            newNode->down->up=newNode;
            this->first=newNode;
            if(this->maxNr<wnr)this->maxNr=wnr;
            if(msg)cout<<"Added "<<wnr<<" new head row. ";
            return;
        }
        while(i<row)
        {
            if(current->down==NULL)
            {
                cout<<"Add Node: Neighbor row not found.\n";
                return;
            }
            current=current->down;
            i++;
        }
        newNode->up=current;
        newNode->down=current->down;
        current->down=newNode;
        if(newNode->down!=NULL)newNode->down->up=newNode;
        current=current->right;
        while(current!=NULL)
        {
            if(current->down==NULL)break;
            current->down->up=NULL;
            current->down=NULL;
            current=current->right;
        }
        if(this->maxNr<wnr)this->maxNr=wnr;
        if(msg)cout<<"Added "<<wnr<<" new row. ";
        return;
    }
    while(i<row)
    {
        if(current->down==NULL)
        {
            cout<<"Add Node: Neighbor row not found.\n";
            return;
        }
        current=current->down;
        i++;
    }
    i=1;
    while(i<col)
    {
        if(current->right==NULL)
        {
            cout<<"Add Node: Neighbor column not found.\n";
            return;
        }
        current=current->right;
        i++;
    }
    if(row==0 && col==0)
    {
        newNode->right=current;
        current->left=newNode;
        if(current->down!=NULL)
        {
            newNode->down=current->down;
            newNode->down->up=newNode;
            current->down=current->down->right;
        }
        this->first=newNode;
        current=current->right;
        if(msg)cout<<"Added "<<wnr<<" new head. ";
    }
    else if(col==0)
    {
        newNode->right=current;
        current->left=newNode;
        if(current->down!=NULL)
        {
            newNode->down=current->down;
            newNode->down->up=newNode;
            current->down=current->down->right;
            if(current->down!=NULL)current->down->up=current;
        }
        if(current->up!=NULL)
        {
            newNode->up=current->up;
            newNode->up->down=newNode;
            current->up=current->up->right;
            if(current->up!=NULL)current->up->down=current;
        }
        current=current->right;
        if(msg)cout<<"Added "<<wnr<<" middle. ";
    }
    else
    {
        newNode->left=current;
        if(current->up!=NULL)newNode->up=current->up->right;
        if(current->down!=NULL)newNode->down=current->down->right;
        newNode->right=current->right;
        current->right=newNode;
        if(newNode->right!=NULL)newNode->right->left=newNode;
        if(newNode->up!=NULL)newNode->up->down=newNode;
        if(newNode->down!=NULL)newNode->down->up=newNode;
        current=current->right->right;
        if(msg)cout<<"Added "<<wnr<<" middle. ";
    }
    while(current!=NULL)
    {
        if(current->up!=NULL)
        {
            current->up->down=current->left;
            current->up=current->up->right;
        }
        if(current->down!=NULL)
        {
            current->down->up=current->left;
            current->down=current->down->right;
        }
        current=current->right;
    }
    if(this->maxNr<wnr)this->maxNr=wnr;
    return;
}
void Net::delNode(int row, int col, bool msg)
{
    Node *current=this->first, *aux;
    if(current==NULL)
    {
        cout<<"Delete Node: No nodes to delete.\n";
        return;
    }
    int i=1;
    while(i<row)
    {
        if(current->down==NULL)
        {
            cout<<"Delete Node: Node row not found.\n";
            return;
        }
        current=current->down;
        i++;
    }
    i=1;
    while(i<col)
    {
        if(current->right==NULL)
        {
            cout<<"Delete Node: Node column not found.\n";
            return;
        }
        current=current->right;
        i++;
    }
    if(current->left==NULL && current->right==NULL)
    {
        aux=current;
        if(current->up==NULL)
        {
            this->first=current->down;
            if(current->down!=NULL)current->down->up=NULL;
        }
        else
        {
            current->up->down=current->down;
            if(current->down!=NULL)
            {
                current->down->up=current->up;
                aux=current->up->right;
                while(aux!=NULL)
                {
                    if(aux->left->down->right==NULL)break;
                    aux->down=aux->left->down->right;
                    aux->down->up=aux;
                    aux=aux->right;
                }
            }
        }
        if(msg)cout<<"Removed "<<current->nr<<".";
        free(current);
        return;
    }
    if(current->up==NULL && current->left==NULL && current->right!=NULL) this->first=current->right;
    aux=current;
    while(aux!=NULL)
    {
        if(aux->up!=NULL)
        {
            aux->up->down=aux->right;
            aux->up=aux->up->left;
        }
        if(aux->down!=NULL)
        {
            aux->down->up=aux->right;
            aux->down=aux->down->left;
        }
        if(aux->right==NULL)break;
        aux=aux->right;
    }
    if(aux->left!=NULL && aux->left->up!=NULL)aux->up=aux->left->up->right;
    if(aux->left!=NULL && aux->left->down!=NULL)aux->down=aux->left->down->right;
    if(current->left!=NULL)current->left->right=current->right;
    if(current->right!=NULL)current->right->left=current->left;
    if(msg)cout<<"Removed "<<current->nr<<".";
    free(current);
    return;
}
void Net::swapNode(int row1, int col1, int row2, int col2, bool msg)
{
    Node *current1=this->first, *current2=this->first;
    if(current1==NULL)
    {
        cout<<"Swap Nodes: Nodes not found.\n";
        return;
    }
    int i=1;
    while(i<row1)
    {
        if(current1->down==NULL)
        {
            cout<<"Swap Nodes: First node not found.\n";
            return;
        }
        current1=current1->down;
        i++;
    }
    i=1;
    while(i<col1)
    {
        if(current1->right==NULL)
        {
            cout<<"Swap Nodes: First node not found.\n";
            return;
        }
        current1=current1->right;
        i++;
    }
    i=1;
    while(i<row2)
    {
        if(current2->down==NULL)
        {
            cout<<"Swap Nodes: Second node not found.\n";
            return;
        }
        current2=current2->down;
        i++;
    }
    i=1;
    while(i<col2)
    {
        if(current2->right==NULL)
        {
            cout<<"Swap Nodes: Second node not found.\n";
            return;
        }
        current2=current2->right;
        i++;
    }
    i=current1->nr;
    current1->nr=current2->nr;
    current2->nr=i;
    if(msg)cout<<"Swapped "<<current2->nr<<" and "<<current1->nr<<".";
    return;
}
void Net::moveNode(int row1, int col1, int row2, int col2, bool msg)
{
    Node *current1=this->first, *current2=this->first;
    if(current1==NULL)
    {
        cout<<"No nodes to move.\n";
        return;
    }
    int ogRow=1,ogCol=1,nwRow=1,nwCol=1,i=1;
    while(ogRow<row1)
    {
        if(current1->down==NULL)
        {
            cout<<"Move Node: Original node row not found.\n";
            return;
        }
        current1=current1->down;
        ogRow++;
    }
    while(ogCol<col1)
    {
        if(current1->right==NULL)
        {
            cout<<"Move Node: Original node column not found.\n";
            return;
        }
        current1=current1->right;
        ogCol++;
    }
    i=current1->nr;
    while(nwRow<row2)
    {
        if(current2->down==NULL)
        {
            addNode(current1->nr,nwRow,0,true,false);
            this->delNode(ogRow,ogCol,false);
            if(msg)cout<<"Moved "<<i<<" to ["<<nwRow+1<<" "<<1<<"].";
            return;
        }
        current2=current2->down;
        nwRow++;
    }
    while(nwCol<col2)
    {
        if(current2->right==NULL)
        {
            cout<<"Move Node: New column not found.\n";
            return;
        }
        current2=current2->right;
        nwCol++;
    }
    if(col2==0)this->addNode(current1->nr,nwRow,0,false,false);
    else this->addNode(current1->nr,nwRow,nwCol,false,false);
    this->delNode(ogRow,ogCol,false);
    if(msg)cout<<"Moved "<<i<<" to ["<<nwRow<<" "<<nwCol+1<<"].";
}
void Net::boxNet(bool msg)
{
    Node *current1, *current2;
    if(this->first==NULL)
    {
        cout<<"No nodes to box.";
        return;
    }
    int i,j,row1,col1,row2,col2,nodeNr=this->countNodes(false),cols=(int)sqrt(nodeNr),rows=cols;
    bool notDone=true, notFound=true;
    if(cols*cols<nodeNr)rows++;
    if(nodeNr-cols*cols>cols)cols++;
    while(notDone)
    {
        notDone=false;
        notFound=true;
        i=1;
        for(current1=this->first; current1!=NULL; current1=current1->down)
        {
            j=1;
            for(current2=current1; current2!=NULL; current2=current2->right)
            {
                if(notFound && i==rows && j<=cols && current2->right==NULL)
                {
                    row1=i;
                    col1=j;
                    notFound=false;
                }
                if(notFound && j>cols && current2->right==NULL)
                {
                    row1=i;
                    col1=j;
                    notFound=false;
                }
                j++;
            }
            if(notFound && i>rows && current1->down==NULL)
            {
                row1=i;
                col1=j-1;
                notFound=false;
            }
            i++;
        }
        notFound=true;
        i=1;
        for(current1=this->first; current1!=NULL; current1=current1->down)
        {
            j=1;
            for(current2=current1; current2!=NULL; current2=current2->right)
            {
                if(notFound && j<cols && current2->right==NULL && row1!=i)
                {
                    row2=i;
                    col2=j;
                    this->moveNode(row1,col1,row2,col2,false);
                    notFound=false;
                    notDone=true;
                }
                j++;
            }
            if(notFound && i<rows && current1->down==NULL)
            {
                row2=i;
                col2=j;
                this->moveNode(row1,col1,row2+1,1,false);
                notFound=false;
                notDone=true;
            }
            i++;
        }
    }
    if(msg)cout<<"Reshaped the net into columns of maximum "<<cols<<" numbers.";
}
void Net::sortNet(bool msg)
{
    Node *current1, *current2;
    if(this->first==NULL)
    {
        cout<<"No nodes to box.";
        return;
    }
    int i,j,row1,col1,row2,col2;
    bool notDone=true;
    while(notDone)
    {
        notDone=false;
        i=1;
        for(current1=this->first; current1!=NULL; current1=current1->down)
        {
            j=1;
            for(current2=current1; current2!=NULL; current2=current2->right)
            {
                if(current2->right!=NULL && current2->nr>current2->right->nr)
                {
                    swapNode(i,j,i,j+1,false);
                    notDone=true;
                }
                else if(current2->right==NULL && current1->down!=NULL && current2->nr>current1->down->nr)
                {
                    swapNode(i,j,i+1,1,false);
                    notDone=true;
                }
                j++;
            }
            i++;
        }
    }
    if(msg)cout<<"Sorted the net.";
}
