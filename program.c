#include <stdio.h>
#include <math.h> 
#define MAX_SIZE 20
struct Matrix {
 float array[MAX_SIZE][MAX_SIZE];
 int m,n;
}A, B, Out, temp;
void cofac(float matrix[][20], int k, struct Matrix *matric);
float determinan(float matrix[][20], int k);
void printArray2(float q[][20], int k){
	int x=0,y=0;
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			printf("%f ",q[i][j]);
		}
		printf("\n");
	}
}
struct Matrix readMatrix(){
	int u,n,m;
	struct Matrix mat;
	printf("Enter the number of row and columns\n");
	scanf("%d %d", &n, &m);
	printf("Enter the Matrix elements\n");
	mat.n=n;mat.m=m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&u);
			mat.array[i][j]=u;
		}
	}
	printf("I get your Matrix!\n");
	return mat;
}
struct Matrix readMatrixFile(){
	int u,n,m;
	struct Matrix mat;
	FILE *fp;
    fp = fopen("./Input.txt", "r+");
    fscanf(fp, "%d %d", &n, &m);
	mat.n=n;mat.m=m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			fscanf(fp,"%d",&u);
			mat.array[i][j]=u;
		}
	}
	fclose(fp);
	printf("I get your Matrix!\n");

	return mat;
}
void printMatrix(struct Matrix *mat){
	int n = mat -> n, m = mat -> m;
	if (n==0 || m==0){
		printf("The Matrix is Empty\n");
	}else{
		printf("%d %d\n", n, m);
		for(int i=0;i<n;i++){
			for(int j=0; j<m; j++){
				printf("%lf ",mat->array[i][j]);
			}
			printf("\n");
		}
	}
}
void printMatrixFile(struct Matrix *mat){
	FILE *fp;
    fp = fopen("./Output.txt", "w+");
	int n = mat -> n, m = mat -> m;
	if (n==0 || m==0){
		fprintf(fp, "The Matrix is Empty\n");
	}else{
		fprintf(fp, "%d %d\n", n, m);
		for(int i=0;i<n;i++){
			for(int j=0; j<m; j++){
				fprintf(fp, "%lf ",mat->array[i][j]);
			}
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
int addMatrix(struct Matrix *mat1, struct Matrix *mat2, struct Matrix *mat3){
	if(!(mat1->m==mat2->n && mat1->n==mat2->m))return 0;
	else{
		mat3->n = mat1 -> n;mat3->m = mat1 -> m;
		for(int i=0;i<mat1->n;i++){
			for(int j=0;j<mat1->m;j++){
				mat3->array[i][j] = mat1->array[i][j] + mat2->array[i][j];
			}
		}
		return 1;
	}
}
int subMatrix(struct Matrix *mat1, struct Matrix *mat2, struct Matrix *mat3){
	if(!(mat1->m==mat2->n && mat1->n==mat2->m))return 0;
	else{
		for(int i=0;i<mat1->n;i++){
			for(int j=0;j<mat1->m;j++){
				mat3->array[i][j] = mat2->array[i][j] - mat1->array[i][j];
			}
		}
		return 1;
	}
}
int mulMatrix(struct Matrix *mat1, struct Matrix *mat2, struct Matrix *mat3){
	if(!(mat1->n==mat2->m))return 0;
	else{
	for(int i=0;i<mat1->n;i++){
			for(int j=0;j<mat2->m;j++){
				mat3->array[i][j] = 0;
				for(int k=0; k < mat1->m;k++){
					mat3->array[i][j] += mat1->array[i][k] * mat2->array[k][j];
				}
			}
		}
		return 1;
	}
}
float detMatrix(struct Matrix *mat){
	float matrix[20][20];
	int n=mat->n,m=mat->m;
	if(n==m){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				matrix[i][j]=mat->array[i][j];
			}
		}
		return determinan(matrix,n);
	}else{
		return 0;
	}
}
void transposeMatrix(struct Matrix *mat){
	int n=mat->n, m=mat->m;
	float matrix[m][n];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			matrix[j][i]=mat->array[i][j];
		}
	}
	mat->n=m, mat->m=n;
	for(int i=0; i<m;i++){
		for(int j=0; j<n;j++){
			mat->array[i][j]=matrix[i][j];
		}
	}
}
void inverseMatrix(struct Matrix *mat){
	int n = mat->n, m = mat->m;
	float matrix[20][20],inv[20][20];
	if (n==m){
		int determinant=detMatrix(mat);
		if(determinant==0){printf("We cant inverse this Matrix\n");}
		else{
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					matrix[i][j] = mat->array[i][j];
				}
			}
			cofac(matrix,n,&Out);
			printArray2(Out.array,n);
		}
	}else{
		printf("Your command is invalid we cant inverse matrix with diffrent row and columns\n");
	}
}
void showMenu(){
	printf("There are some command that i can do for you!\n");
	printf("for example i can take Matrix from you by command <<1 A>> or <<1 B>>\n");
	printf("for example i can add two Matrices by command 2\n");
	printf("for example i can sub two Matrices by command 3\n");
	printf("for example i can multiply two Matrices by command 4\n");
	printf("for example i can determinant Matrix by command <<5 A>> or <<5 B>>\n");
	printf("for example i can transpose Matrix by command <<6 A>> or <<6 B>>\n");
	printf("I can show your matrix that you give me by command <<7 A>>(for showing matix A)or <<7 B>>(for showing matix B) or <<7 Out>>(for showing the result of command 2 or 3 or 4)\n");
	printf("for example i can inverse Matrix by command <8 A> or <8 B> \n");
}
int main(){
	A.n=0;A.m=0;B.n=0;B.m=0;Out.n=0;Out.m=0;
	showMenu();
	int command,fl=1,t;
	char s[3], where[3];
	while (fl){
		scanf("%d",&command);
		switch (command)
		{
		case 0:
			showMenu();
			break;
		case 1:
			//printf("TEST");
			scanf("%s",s);
			printf("Read from Console or File(C/F)?");
			scanf("%s", where);
			if(s[0]=='A'){
				if(where[0]=='C')
					A=readMatrix();
				if(where[0]=='F')
					A=readMatrixFile();
			}else if(s[0]=='B'){
				if(where[0]=='C')
					B=readMatrix();
				if(where[0]=='F')
					B=readMatrixFile();
			}else{
				printf("your command is invalid you can show menu by <0>\n");
			}
			break;
		case 2:
			t=addMatrix(&A, &B, &Out);
			if (t)
				printf("The Output is save in the Matrix Out you can see the output by command <7 O>\n");
			else
				printf("we cant add two matrices with diffrent row and columns ! \n");
			break;
		case 3:
			t= subMatrix(&A, &B, &Out);
			if (t)
				printf("The Output is save in the Matrix Out you can see the output by command <7 O>\n");
			else
				printf("we cant sub two matrices with diffrent row and columns ! \n");
			break;
		case 4:
			t=mulMatrix(&A, &B, &Out);
			if (t)
				printf("The Output is save in the Matrix Out you can see the output by command <7 O>\n");
			else
				printf("the columns of matrix A is diffrent from the row of matrix B\n");
			break;
		case 5:
			scanf("%s",s);
			float det;
			if(s[0]=='A')
				det=detMatrix(&A);
			else
				det=detMatrix(&B);
			printf("The determinant of matrix is : %f \n",det);
			break;
		case 6:
			scanf("%s",s);
			if(s[0]=='A')
				transposeMatrix(&A);
			else
				transposeMatrix(&B);
			printf("Your command has successfully done\n");
			break;
		case 7:
			scanf("%s",s);
			printf("Write in Console or File(C/F)?");
			scanf("%s",where);
			if(s[0]=='A'){
				if(where[0]=='C')
					printMatrix(&A);
				else if(where[0]=='F')
					printMatrixFile(&A);
				else
					printf("Your command is invalid you can show menu by command <0> : ");
			}else if(s[0]=='B'){
				if(where[0]=='C')
					printMatrix(&B);
				else if(where[0]=='F')
					printMatrixFile(&B);
				else
					printf("Your command is invalid you can show menu by command <0> : ");
			}else if(s[0]=='O'){
				if(where[0]=='C')
					printMatrix(&Out);
				else if(where[0]=='F')
					printMatrixFile(&Out);
				else
					printf("Your command is invalid you can show menu by command <0> : ");
			}else
				printf("Your command is invalid you can show menu by command <0> : ");
			break;
		case 8:
			scanf("%s",s);
			if(s[0]=='A'){
				inverseMatrix(&A);
			}else if(s[0]=='B'){
				inverseMatrix(&B);
			}else if(s[0]=='O'){
				inverseMatrix(&Out);
			}else{
				printf("Your command is invalid you can show menu by command <0> : ");
			}
			break;
		case 10:
			fl=0;
			break;
		default:
			printf("The command is invalid you can show the menu by command <0> or you can exit the program by command <10> : ");
			break;
		}
	}
	printf("Thank You for using my program goodbye!\n");
	return 0;
}
int ipk(int m){
	if (m%2==1)return -1;
	return 1;
}

float determinan(float matrix[][20], int k){
	float det=0;
	//printArray2(matrix,k);
	if(k>2){
		float a[20][20];
		for(int i=0;i<k;i++){
			int x=0,y=0;
			for(int j=0;j<k;j++){
				for(int h=0;h<k;h++){
					
					if(h!=i && j!=0){
						a[x][y]=matrix[j][h];
						y++;
					}
					if(y==k-1){y=0;x++;}
				}
			}
			det+=matrix[0][i]*ipk(i)*determinan(a, k-1);
		}
	}
	else{
		float kho=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
		return kho;
	}
}
void cofac(float mat[][20], int k, struct Matrix *matric){
	float det=determinan(mat,k);
	if(det!=0){
		int x=0,y=0;
		det=1/det;
		float matrix[20][20];
		float inv[20][20];
		for(int i=0;i<k;i++){
			for(int j=0;j<k;j++){
				x=y=0;
				for(int h=0;h<k;h++){
					for(int t=0;t<k;t++){
						if(h!=i && t!=j){
							matrix[x][y]=mat[h][t];
							y++;
						}
						if(y==k-1){y=0;x++;}
					}
				}
				inv[i][j]=determinan(matrix, k-1);
			}
		}
		for(int i=0;i<k;i++){
			for(int j=0;j<k;j++){
				matric->array[j][i]=ipk(i+j)*det*inv[i][j];
			}
		}
		matric->m=k;matric->n=k;
	}
}
