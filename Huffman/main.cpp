#include <iostream>
using namespace std;

int m, s1, s2;      // m���ܽ�������s1,s2����ɸѡ����С�͵ڶ�С��������

typedef struct{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;      //��̬��������洢��������

typedef char* HuffmanCode;   //��̬��������洢�����������

//ѡ��weight��С���������,s1������С�ģ�s2����ڶ�С��
void SelectMin(HuffmanTree HT, int nNode)
{
    int i, j;
    for(i = 1; i <= nNode; i++)
        if(!HT[i].parent)
        {
            s1 = i;
            break;
        }
    for(j = i+1; j <= nNode; j++)
        if(!HT[j].parent)
        {
            s2 = j;
            break;
        }

    for(i = 1; i <= nNode; i++)
        if((HT[i].weight < HT[s1].weight) && (!HT[i].parent) && (s2 != i))
            s1 = i;
    for(j = 1; j <= nNode; j++)
        if((HT[j].weight < HT[s2].weight) && (!HT[j].parent) && (s1 != j))
            s2 = j;
    // ����ֻɸѡ����С�����������ﱣ֤s1��weight��s2��С
    if(HT[s1].weight > HT[s2].weight)
    {
        int tmp = s1;
        s1 = s2;
        s2 = tmp;
    }
}

// w[]���nNode���ַ���Ȩֵ��������0���������������HT��
// �����nNode���ַ��Ĺ���������HC
void HuffmanCoding(HuffmanTree &HT, HuffmanCode *&HC, int *w, int nNode)
{
    int i;
    char *hfcode;
    int p;
    //int cdlen;
    if(nNode < 1)
        return;
    m = 2*nNode-1;   //���������Ľ����������ʽ

    /////////////////////////////��������Huffman���ĳ�ʼ��/////////////////////////////
    HT = (HTNode*) malloc ((m+1) *sizeof(HTNode));  //0�ŵ�Ԫδ��
    for(i = 1; i <= nNode; i++)    //��ʼ��
    {
        HT[i].weight = w[i-1];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i = nNode+1; i <= m; i++)
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    /////////////////////////////������Huffman���Ĺ���/////////////////////////////
    for(i = nNode+1; i <= m; i++)
    {
        // ������������
        // ��HT[1..i-1]��ѡ��parentΪ0��weight��С�������ڵ�
        // ����ŷֱ���s1��s2,����С��������
        SelectMin(HT, i-1);
        HT[s1].parent = i;
        HT[s2].parent = i;
        //cout << "S1 && S2: " << HT[s1].weight << " " << HT[s2].weight << endl;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }


    /////////////////////////////��������Huffman���ı���/////////////////////////////

    ////////////////////////����һ///////////////////////////
    /*�÷����Ǵ�ÿ��Ҷ��㿪ʼ���ݣ��ԴӺ���ǰ�ķ�ʽ����huffman����*/
    hfcode = (char *) malloc ( (nNode + 1) * sizeof( char ) );
    hfcode[nNode] = '\0';   //�����ԡ�\0����β
    int start;
    int c;   //c:��ǰ����ڵ㣬p��c�ĸ����
    for(int i=1; i<=nNode; i++)
    {
        start = nNode;
        for(c=i, p=HT[c].parent; p!=0; c=p,p=HT[p].parent)
        {
            if(c==HT[p].lchild)
                hfcode[--start]='0';
            else if(c==HT[p].rchild)
                hfcode[--start]='1';
        }
        //�����㹻��Ÿýڵ������У����˷�;
        HC[i] = (char *) malloc ((nNode-start+1) * sizeof(char));
        strcpy(HC[i], &hfcode[start]);
    }
    free(hfcode);

    ////////////////////////������///////////////////////////
    // �÷����Ӹ�����,�ݹ������������,��ñ��롣���0��1��2�������£�
    //0:�ѵ�һ�������������½��
    //1:��ǰ����������ӽ��Ľ�㣬��û�л��ݻ���
    //2:�������������߶��ӽ����ȫ�����꣬�Ѿ����ݻ���������ݵ��丸���
    //ע��:�������ߵ�һ����������������Ϊ��һ״̬��
    //����0->1->2->0(���һ��2->0���Ǳ����)����ִ��������Ȼ�ǵ�ǰ״̬

    /*hfcode = (char *) malloc (nNode * sizeof(char));   //���������Ĺ����ռ�
    p = m;
    cdlen = 0;
    for(i = 1; i <= m; i++)
        HT[i].weight = 0;   //������������ʱ�������״̬�ı�־

    while(p)        //�˳�������p = ���m��parent,��Ϊ0
    {
        if(HT[p].weight == 0)       //������
        {
            HT[p].weight = 1;
            if(HT[p].lchild != 0)
            {
                p = HT[p].lchild;
                hfcode[cdlen++] = '0';
            }
            //else if(HT[p].rchild == 0)  //���Һ��Ӷ�Ϊ0��Ҷ���
            //{
            //  HC[p] = (char *) malloc ((cdlen+1) * sizeof(char));
            //  hfcode[cdlen] = '\0';   //��֤����Ĳ��ᱻ����
            //  strcpy(HC[p], hfcode);   //���Ʊ���
            //}
        }
        else if(HT[p].weight == 1)   //������
        {
            HT[p].weight = 2;
            if(HT[p].rchild != 0)
            {
                p = HT[p].rchild;
                hfcode[cdlen++] = '1';
            }
            //�÷�֧���������ƺ�������һ�㣬�����汻ע�͵��ĵط�Ҳ����
            else if(HT[p].rchild == 0)  //���Һ��Ӷ�Ϊ0��Ҷ���
            {
                HC[p] = (char *) malloc ((cdlen+1) * sizeof(char));
                hfcode[cdlen] = '\0';   //��֤����Ĳ��ᱻ����
                strcpy(HC[p], hfcode);   //���Ʊ���
            }
        }
        else    //HT[p].weight == 2 �˻ص�����㣬���볤�ȼ�һ
        {
            HT[p].weight = 0;
            p = HT[p].parent;
            --cdlen;
        }
    }*/
}
/*Huffman���뺯��
 *HT:Huffman����w[]:Ȩֵ����(���±�0��ʼ)��code[]:Ҫ����Ĵ�
 */
void HuffmanDecode(HuffmanTree HT, int w[], char code[])
{
    char *ch = code;
    int i;
    while( *ch != '\0' ){
        //����һ�����ÿ�ζ�������m��ʼ
        for(i=m; HT[i].lchild !=0 && HT[i].rchild != 0; ){
            if( *ch == '0' )
                i = HT[i].lchild;
            else if( *ch == '1' )
                i = HT[i].rchild;
            ++ch;
        }
        cout<<w[i-1]<<" ";
    }
}

int main()
{
    HuffmanTree HT = NULL;   // ��������
    HuffmanCode *HC;    // �������������
    int *w, nNode, i;   // w��¼Ȩֵ
    char CodeStr[20]= {0};  //��ű����Ĵ�
    cout<<"number of the node:(>=2): "<<endl;
    cin>>nNode;
    HC = (HuffmanCode *) malloc (nNode* sizeof(HuffmanCode));
    w = (int *) malloc (nNode * sizeof(int));
    cout<<"enter: "<<nNode<<" weight\n";
    for(i = 0; i < nNode; i++)
        scanf("%d", &w[i]);
    HuffmanCoding(HT, HC, w, nNode);
    cout<<"\nHuffmanCoding:"<<endl;
    for(i = 1; i <= nNode; i++){
        printf("%2d(%d):%s\n", i, w[i-1], HC[i]);
        strcat(CodeStr, HC[nNode-i+1]); //������һ��huffman�봮
    }

    cout<<"Huffman's\""<<CodeStr<<"\"decoding:"<<endl;
    HuffmanDecode(HT, w, CodeStr);

    return 0;
}
