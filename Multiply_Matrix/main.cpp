#include <iostream>

using namespace std;

const int N=4; //����N�����������Ĵ�С

int main()
{
    void STRASSEN(int n,float A[][N],float B[][N],float C[][N]);
    void input(int n,float p[][N]);
    void output(int n,float C[][N]);                    //������������

    float A[N][N],B[N][N],C[N][N];  //������������A,B,C

    cout<<"enter matrix A[N][N]:"<<endl<<endl;
    input(N,A);
    cout<<endl<<"enter matrix B[N][N]:"<<endl<<endl;
    input(N,B);                         //¼������

    STRASSEN(N,A,B,C);   //����STRASSEN��������

    output(N,C);  //���������
    return 0;
}


void input(int n,float p[][N])  //�������뺯��
{
    int i,j;

    for(i=0;i<n;i++)
    {
        cout<<"Please enter "<<i+1<<"line"<<endl;
        for(j=0;j<n;j++)
            cin>>p[i][j];
    }
}

void output(int n,float C[][N]) //�ݾ����������
{
    int i,j;
    cout<<"Matrix:"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<endl;
        for(j=0;j<n;j++)
            cout<<C[i][j]<<"  ";
    }
    cout<<endl<<endl;

}

void MATRIX_MULTIPLY(float A[][N],float B[][N],float C[][N])  //��ͨ���ľ���˷�����C=AB�����㷨(����2��)
{
    int i,j,t;
    for(i=0;i<2;i++)                     //����A*B-->C
        for(j=0;j<2;j++)
        {
            C[i][j]=0;                   //������һ��C[i][j]��C[i][j]Ӧ���¸�ֵΪ��
            for(t=0;t<2;t++)
            C[i][j]=C[i][j]+A[i][t]*B[t][j];
        }
}

void MATRIX_ADD(int n,float X[][N],float Y[][N],float Z[][N]) //����ӷ�����X+Y��>Z
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            Z[i][j]=X[i][j]+Y[i][j];
}

void MATRIX_SUB(int n,float X[][N],float Y[][N],float Z[][N]) //�����������X-Y��>Z
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            Z[i][j]=X[i][j]-Y[i][j];

}


void STRASSEN(int n,float A[][N],float B[][N],float C[][N])  //STRASSEN�������ݹ飩
{
    float A11[N][N],A12[N][N],A21[N][N],A22[N][N];
    float B11[N][N],B12[N][N],B21[N][N],B22[N][N];
    float C11[N][N],C12[N][N],C21[N][N],C22[N][N];
    float M1[N][N],M2[N][N],M3[N][N],M4[N][N],M5[N][N],M6[N][N],M7[N][N];
    float AA[N][N],BB[N][N],MM1[N][N],MM2[N][N];

    int i,j;//,x;


    if (n==2)
        MATRIX_MULTIPLY(A,B,C);//��ͨ���ľ���˷�����C=AB�����㷨(����2��)
    else
    {
        for(i=0;i<n/2;i++)
            for(j=0;j<n/2;j++)

                {
                    A11[i][j]=A[i][j];
                    A12[i][j]=A[i][j+n/2];
                    A21[i][j]=A[i+n/2][j];
                    A22[i][j]=A[i+n/2][j+n/2];
                    B11[i][j]=B[i][j];
                    B12[i][j]=B[i][j+n/2];
                    B21[i][j]=B[i+n/2][j];
                    B22[i][j]=B[i+n/2][j+n/2];
                }       //������A��Bʽ��Ϊ�Ŀ�




    MATRIX_SUB(n/2,B12,B22,BB);
    STRASSEN(n/2,A11,BB,M1);//M1=A11(B12-B22)

    MATRIX_ADD(n/2,A11,A12,AA);
    STRASSEN(n/2,AA,B22,M2);//M2=(A11+A12)B22

    MATRIX_ADD(n/2,A21,A22,AA);
    STRASSEN(n/2,AA,B11,M3);//M3=(A21+A22)B11

    MATRIX_SUB(n/2,B21,B11,BB);
    STRASSEN(n/2,A22,BB,M4);//M4=A22(B21-B11)

    MATRIX_ADD(n/2,A11,A22,AA);
    MATRIX_ADD(n/2,B11,B22,BB);
    STRASSEN(n/2,AA,BB,M5);//M5=(A11+A22)(B11+B22)

    MATRIX_SUB(n/2,A12,A22,AA);
    MATRIX_ADD(n/2,B21,B22,BB);
    STRASSEN(n/2,AA,BB,M6);//M6=(A12-A22)(B21+B22)

    MATRIX_SUB(n/2,A11,A21,AA);
    MATRIX_ADD(n/2,B11,B12,BB);
    STRASSEN(n/2,AA,BB,M7);//M7=(A11-A21)(B11+B12)
    //����M1,M2,M3,M4,M5,M6,M7���ݹ鲿�֣�


    MATRIX_ADD(N/2,M5,M4,MM1);
    MATRIX_SUB(N/2,M2,M6,MM2);
    MATRIX_SUB(N/2,MM1,MM2,C11);//C11=M5+M4-M2+M6

    MATRIX_ADD(N/2,M1,M2,C12);//C12=M1+M2

    MATRIX_ADD(N/2,M3,M4,C21);//C21=M3+M4

    MATRIX_ADD(N/2,M5,M1,MM1);
    MATRIX_ADD(N/2,M3,M7,MM2);
    MATRIX_SUB(N/2,MM1,MM2,C22);//C22=M5+M1-M3-M7

    for(i=0;i<n/2;i++)
        for(j=0;j<n/2;j++)
        {
            C[i][j]=C11[i][j];
            C[i][j+n/2]=C12[i][j];
            C[i+n/2][j]=C21[i][j];
            C[i+n/2][j+n/2]=C22[i][j];
        }                                            //�������ͻ�C[N][N]

    }

}
