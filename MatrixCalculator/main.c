//Ивлев Александр РКТ1-31	
#include <stdio.h>   
#include <stdlib.h>
#include <conio.h>
#include <errno.h>
#include <Windows.h>

void dynamic_array_print(float** A, int N, int M);
float **dynamic_array_alloc(int N, int M);
void dynamic_array_free(float** A, int N);
void _alert();
float Gauss_Determinant(float** A, int N);
void Sum_Of_2_Matrix(float** A, float** B, float** C, int N, int M);
void Prod_Of_2_Matrix(float** A, float** B, float** C, int N, int M, int Q);
void Swap(float** A, int row1, int row2, int M);
int Rank_Of_Matrix(float** A, int N, int M);
float** ptrs_to_values(float* data, int N, int M);
float* values_to_ptrs(float** A, int N, int M);
double Determinant(double** A, int N);

int main(){
	char filename[30], filename1[30];
	int x, y;
	int command;			
	int n, num, filesize, numwritten;
	int i, j, k;
	int row1, row2, row3;
	int col1, col2, col3;
	float new_elem;
	float** a;
	float** b;
	float** ans;
	float det;
	float* data;
	double** a_double;
	int rank;
	errno_t err;
	FILE *fPtr1;
	FILE *fPtr2;
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
 
	printf("Выполнил Ивлев Александр РКТ1-31\n");
	_alert();
 	
	while (scanf_s("%d", &command, 1)){
		while (command > 8 || command < 0){
				printf("Введите корректную команду : ");
				scanf_s("%d", &command, 1);				
			}
			
		switch (command){
			case 0:
				printf("Работа завершена\n");
				return 0;
			case 1:
				n = 2;
				printf("Введите количество строк и столбцов матрицы: ");
				scanf_s("%d %d", &row1, &col1, 2);
				num = row1 * col1;
 				
	    		a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break;
				}
				
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
 				
				printf("Введите имя файла : ");
				scanf_s("%s", filename, 30);
				err = fopen_s(&fPtr1, filename, "w");
				if (err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break; 	
			 	}
				else{
					printf("\n");
				}
				printf("Введите элементы матрицы:\n");
				printf("----------------------\n");
				k = 0;
				for (i = 0; i < row1; ++i){
					for (j = 0; j < col1; ++j){
						k++;
						printf("Введите элемент a[%d]: ", k);
						scanf_s("%f", (data + i * col1 + j), 1);
					}
				}
				
				a = ptrs_to_values(data, row1,  col1);
				printf("----------------------\n");
				printf("Порядок матрицы = %d\n", n);
				printf("Количество строк = %d\n", row1);
				printf("Количество столбцов = %d\n", col1);
				printf("Вывод элементов матрицы:\n");
				printf("Количество элементов матрицы = %d\n", num);
				 
				fwrite((int*)&n, sizeof(int), 1, fPtr1);
				fwrite((int*)&row1, sizeof(int), 1, fPtr1);
				fwrite((int*)&col1, sizeof(int), 1, fPtr1);
				numwritten = fwrite((float*)data, sizeof(float), num, fPtr1);
				
				printf_s("numwritten = %d\n", numwritten, 1);
				fclose(fPtr1);
				_alert();
				dynamic_array_free(a, row1);
				free(data);
				break;
 				
			case 2:
				printf("Введите имя файла : ");
				scanf_s("%s", filename, 30);
 
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
 			
				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
				filesize = sizeof(int) * 3;
 				
 				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break;
				}
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				k = fread(data, sizeof(float), num, fPtr1);
				filesize += k * sizeof(float);
				printf("Размер файла: %d байт\n", filesize);
				printf("Количество записей: %d\n", k);
				printf("Число прочитанных элементов: %d\n", k);
				printf("\n");
				
				a = ptrs_to_values(data, row1, col1);
				dynamic_array_print(a, row1, col1);
 
				fclose(fPtr1);
				_alert();
				dynamic_array_free(a, row1);
				free(data);
				
				break;
 
			case 3:
				printf("Введите имя файла : ");
				scanf_s("%s", filename, 30);
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				
 				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
					
				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break;
				}
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				a = ptrs_to_values(data, row1, col1);
				fclose(fPtr1);
					
				printf("----------------------\n");
				printf("Первоначальная матрица\n");
				printf("----------------------\n");
 
				dynamic_array_print(a, row1, col1);
				printf("----------------------\n");
 
				printf("Какой элемент изменить?\n");
				printf("Индекс строки = ");
				scanf("%d", &x);
				x--;
				printf("Индекс столбца = ");
				scanf("%d", &y);
				y--;
				
				printf("Введите новый элемент: ");
				scanf("%f", &new_elem);
				printf("----------------------\n");
 				
 				*(data + x * col1 + y) = (float)new_elem;
 
				printf("Новая матрица\n");
				a = ptrs_to_values(data, row1, col1);
				printf("----------------------\n");
				dynamic_array_print(a, row1, col1);
				printf("----------------------\n");
				
				err = fopen_s(&fPtr1, filename, "w");
				if (err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
			 	}
				else{
					printf("\n");
				}
					
				fwrite((int*)&n, sizeof(int), 1, fPtr1);
				fwrite((int*)&row1, sizeof(int), 1, fPtr1);
				fwrite((int*)&col1, sizeof(int), 1, fPtr1);
				fwrite((float*)data, sizeof(float), num, fPtr1); 
				
				fclose(fPtr1);	
				_alert();
				dynamic_array_free(a, row1);
				free(data);
				
				break;
			
			case 4:
				printf("Введите имя файла : ");
				scanf_s("%s", filename, 30);
 
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
 				
				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
				
				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break;
				}
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				a = ptrs_to_values(data, row1, col1);
				fclose(fPtr1);
				
				
				if (row1 != col1){
					printf("Матрица неквадратная!\n");
				}
				else{
					//det = Gauss_Determinant(a, row1);
					//printf("Детерминант = %.1lf\n", det);
					printf("Исходная матрица :\n");
					dynamic_array_print(a, row1, col1);
					a_double = (double**)malloc(row1 * sizeof(double*));
 					for(i = 0; i < row1; ++i){
        				a_double[i] = (double*)malloc(col1 * sizeof(double));
    				}
    			
    				for (i = 0; i < row1; ++i){
    					for (j = 0; j < col1; ++j){
    						a_double[i][j] = (double)a[i][j];
						}
					}
					printf("det = %.1lf\n", Determinant(a_double, row1));
				}
				_alert();
				dynamic_array_free(a, row1);
				for(i = 0; i < row1; ++i){
        			free(a_double[i]);
    			}
    			free(a_double);
				free(data);
				
				break;
			
			case 5:
				printf("Введите имя первого файла : ");
				scanf_s("%s", filename, 30);
 
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				
				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break; 
				}
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				a = ptrs_to_values(data, row1, col1);
				
				fclose(fPtr1);
				
				printf("Введите имя второго файла : ");
				scanf_s("%s", filename1, 30);
 
				err = fopen_s(&fPtr2, filename1, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				fread((int*)&n, sizeof(int), 1, fPtr2);
				fread((int*)&row2, sizeof(int), 1, fPtr2);
				fread((int*)&col2, sizeof(int), 1, fPtr2);
				num = row2 * col2;
				b = dynamic_array_alloc(row2, col2);
	    		if (b == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break; 
				}
				if (data == NULL){
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				b = ptrs_to_values(data, row2, col2);
				
				fclose(fPtr2);
				
				if ((row1 != row2) || (col1 != col2)){
					printf("Данные матрицы невозможно сложить!\n");
				}
				else{
					ans = dynamic_array_alloc(row1, col1);
					Sum_Of_2_Matrix(a, b, ans, row1, col1);
					printf("Результирующая матрица\n");
					printf("----------------------\n");
					dynamic_array_print(ans, row1, col1);
					dynamic_array_free(ans, row1);	
				}
				
				_alert();
				dynamic_array_free(a, row1);
				dynamic_array_free(b, row2);
				free(data);
				break;
			
			case 6:
				printf("Введите имя первого файла : ");
				scanf_s("%s", filename, 30);
 
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				
				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break; 
				}
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL){
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				a = ptrs_to_values(data, row1, col1);
				
				fclose(fPtr1);
				
				printf("Введите имя второго файла : ");
				scanf_s("%s", filename1, 30);
 
				err = fopen_s(&fPtr2, filename1, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				fread((int*)&n, sizeof(int), 1, fPtr2);
				fread((int*)&row2, sizeof(int), 1, fPtr2);
				fread((int*)&col2, sizeof(int), 1, fPtr2);
					
				b = dynamic_array_alloc(row2, col2);
	    		if (b == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break; 
				}
				if (data == NULL){
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;
				}
				fread(data, sizeof(float), num, fPtr1);
				b = ptrs_to_values(data, row2, col2);
				
				fclose(fPtr2);
				
				row3 = row1;
				col3 = col2;
				ans = dynamic_array_alloc(row3, col3);
				if (row1 != col2){
					printf("Данные матрицы невозможно умножить!\n");
				}
				else{
					Prod_Of_2_Matrix(a, b, ans, row3, col3, col1);
					printf("Результирующая матрица\n");
					printf("----------------------\n");
					dynamic_array_print(ans, row3, col3);
				}
				
				_alert();
				dynamic_array_free(ans, row3);
				dynamic_array_free(a, row1);
				dynamic_array_free(b, row2);
				free(data);
				break;
				
			case 7:
				printf("Введите имя файла : ");
				scanf_s("%s", filename, 30);
 				
				err = fopen_s(&fPtr1, filename, "r");
				if(err){
					puts("Файл не может быть открыт!");
					printf("Ошибка при открытии файла!\n");
					_getch();
					break;
				}
				else{
					printf("\n");
				}
				
				fread((int*)&n, sizeof(int), 1, fPtr1);
				fread((int*)&row1, sizeof(int), 1, fPtr1);
				fread((int*)&col1, sizeof(int), 1, fPtr1);
				num = row1 * col1;
				a = dynamic_array_alloc(row1, col1);
	    		if (a == NULL){
					printf("Ошибка выделения памяти под массив элементов матрицы\n.");
					_getch();
					break; 
				}
				
				data = (float*)calloc(num, sizeof(float));
				if (data == NULL) {
					printf("Ошибка выеделения памяти под массив указателей\n");
					_getch();
					break;;
				}
				fread(data, sizeof(float), num, fPtr1);
				a = ptrs_to_values(data, row1, col1);
				
				fclose(fPtr1);
				
				rank = Rank_Of_Matrix(a, row1, col1);
				printf("Ранг матрицы = %d\n", rank);
				_alert();
				dynamic_array_free(a, row1);
				break;
			}
	}
	
	_getch();	
	return 0;
}
