#include <stdio.h>
int power(int base, int exp){
int i=0, p=1;
while(++i<exp+1 && 1*(p*=base));
return p;
}
void matrixAdd(int* A, int* B, int* C, int n, int x){
int i,j, m=x>0?n/2:n;
for (i=0;i<m;i++)
for (j=0;j<m;j++)
*(C+i*m+j) = *(A+i*n+j) + *(B+i*n+j);
}
void matrixSub(int* A, int* B, int* C, int n, int x){
int i,j, m=x>0?n/2:n;
for (i=0;i<m;i++)
for (j=0;j<m;j++)
*(C+i*m+j) = *(A+i*n+j) - *(B+i*n+j);
}
void strassenMatrix(int* A, int* B, int* C, int n){
int i,j;
if(n==2){
int P=(*A+*(A+n+1))*(*B+*(B+n+1));  //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
int Q=(*(A+n)+*(A+n+1))*(*B);   //Q=(A[1][0]+A[1][1])*B[0][0]
int R=(*A)*(*(B+1)-*(B+n+1));   //R=A[0][0]*(B[0][1]-B[1][1])
int S=(*(A+n+1))*(*(B+n)-*B);   //S=A[1][1]*(B[1][0]-B[0][0])
int T=(*A+*(A+1))*(*(B+n+1));   //T=(A[0][0]+A[0][1])*B[1][1]
int U=(*(A+n)-*A)*(*B+*(B+1));  //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
int V=(*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1));  //V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1])
*C=P+S-T+V;
*(C+1)=R+T;
*(C+n)=Q+S;
*(C+n+1)=P+R-Q+U;
}
else{
int m=n/2, x[m][m], y[m][m], o[n][n];
for(i=0;i<n;i++)
for(j=0;j<n;j++)
o[i][j]=0;
/*P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])*/
int P[m][m];
matrixAdd(A, A+m*(n+1), x, n, 1);
matrixAdd(B, B+m*(n+1), y, n, 1);
strassenMatrix(x, y, P, m);
/*Q=(A[1][0]+A[1][1])*B[0][0]*/
int Q[m][m];
matrixAdd(A+m*n, A+m*(n+1), x, n, 1);
matrixAdd(B, o, y, n, 1);
strassenMatrix(x, y, Q, m);
/*R=A[0][0]*(B[0][1]-B[1][1])*/
int R[m][m];
matrixAdd(A, o, x, n, 1);
matrixSub(B+m, B+m*(n+1), y, n, 1);
strassenMatrix(x, y, R, m);
/*S=A[1][1]*(B[1][0]-B[0][0])*/
int S[m][m];
matrixAdd(A+m*(n+1), o, x, n, 1);
matrixSub(B+m*n, B, y, n, 1);
strassenMatrix(x, y, S, m);
/*T=(A[0][0]+A[0][1])*B[1][1]*/
int T[m][m];
matrixAdd(A, A+m, x, n, 1);
matrixAdd(B+m*(n+1), o, y, n, 1);
strassenMatrix(x, y, T, m);
/*U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])*/
int U[m][m];
matrixSub(A+m*n, A, x, n, 1);
matrixAdd(B, B+m, y, n, 1);
strassenMatrix(x, y, U, m);
/*V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1])*/
int V[m][m];
matrixSub(A+m, A+m*(n+1), x, n, 1);
matrixAdd(B+m*n, B+m*(n+1), y, n, 1);
strassenMatrix(x, y, V, m);
/*Calculating the 4 parts for the result matrix*/
int W[m][m], X[m][m], Y[m][m], Z[m][m];
matrixSub(V,T,x,m,0);
matrixAdd(S,x,y,m,0);
matrixAdd(P,y,W,m,0); // W=P+S-T+V
matrixAdd(R,T,X,m,0); // X==R+T
matrixAdd(Q,S,Y,m,0); // Y=Q+S
matrixAdd(U,Q,x,m,0);
matrixAdd(R,x,y,m,0);
matrixAdd(P,y,Z,m,0); // Z=P+R-Q+U
/*Conquering 4 parts in the result matrix*/
for (i=0;i<m;i++)
for (j=0;j<m;j++){
*(C+i*n+j) = W[i][j]; //C[0][0]=W
*(C+i*n+j+m) = X[i][j]; //C[0][1]=X
*(C+(i+m)*n+j) = Y[i][j]; //C[1][0]=Y
*(C+(i+m)*n+j+m) = Z[i][j]; //C[1][1]=Z
}
}
}
void main()
{
int i,j,k,m,n,n1,n2,n3,n4,o=0;
/*Input first matrix*/
printf("Enter the order of the 1st Matrix (rows and columns):");
scanf("%d%d",&n1,&n2);
int A[n1][n2];
printf("\nNow enter the first matrix:\n\n");
for(i=0;i<n1;i++){
printf("Enter the elements of the %d-th row:",i+1);
for(j=0;j<n2;j++)
scanf(" %d",&A[i][j]);
}
/*Input second matrix*/
printf("\n\nEnter the no. of columns of the 2nd Matrix:");
scanf("%d",&n3);
int B[n2][n3];
printf("\nNow enter the second matrix:\n\n");
for(i=0;i<n2;i++){
printf("Enter the elements of the %d-th row:",i+1);
for(j=0;j<n3;j++)
scanf(" %d",&B[i][j]);
}
/*Creating square matrix of order 2^n for all and initializing all elements to 0 except prefixed*/
n4=n1>n2?n1:n2;
n=n3>n4?n3:n4;
while(n>(m=power(2,++o)));
int a[m][m],b[m][m],C[m][m];
for(i=0;i<m;i++)
for(j=0;j<m;j++){
a[i][j]=0;
b[i][j]=0;
}
for(i=0;i<n1;i++)
for(j=0;j<n2;j++)
a[i][j]=A[i][j];
for(i=0;i<n2;i++)
for(j=0;j<n3;j++)
b[i][j]=B[i][j];
/*Printing first matrix*/
printf("\nThis is the first matrix:");
for(i=0;i<n1;i++){
printf("\n\n\n");
for(j=0;j<n2;j++)
printf("\t%d",a[i][j]);
}
/*Printing second matrix*/
printf("\n\n\nThis is the second matrix:");
for(i=0;i<n2;i++){
printf("\n\n\n");
for(j=0;j<n3;j++)
printf("\t%d",b[i][j]);
}
strassenMatrix(a,b,C,m);    //Calling the function.
/*Printing the final matrix*/
printf("\n\n\nThis is the final matrix:");
for(i=0;i<n1;i++){
printf("\n\n\n");
for(j=0;j<n3;j++)
printf("\t%d",C[i][j]);
}
}
