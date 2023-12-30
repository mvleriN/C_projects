//Ивлев Александр РКТ1-31
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
void dynamic_array_print(float **A, int N, int M){
	int i, j;
 
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            printf("%.1f ", A[i][j]);
        }
        printf("\n");
    }
}

float **dynamic_array_alloc(int N, int M){
	int i;
	float **A;
	A = (float**)malloc(N * sizeof(float*));
 
	for(i = 0; i < N; ++i){
        A[i] = (float*)malloc(M * sizeof(float));
    }
    return A;
}
 
void dynamic_array_free(float **A, int N)
{
	int i;
    for(i = 0; i < N; ++i){
        free(A[i]);
    }
    free(A);
}

void _alert(){
	printf("----------------------\n");
	printf("Нажмите 0 для выхода из программы\n");
	printf("Нажмите 1 для записи матрицы в файл\n");
	printf("Нажмите 2 для проверки файла\n");
	printf("Нажмите 3 для замены элемента матрицы\n");
	printf("Нажмите 4 для вычисления детерминанта\n");
	printf("Нажмите 5 для суммирования двух матриц\n");
	printf("Нажмите 6 для умножения двух матриц\n");
	printf("Нажмите 7 для вычисления ранга матрицы\n");
	printf("----------------------\n");
}

double Gauss_Determinant(float** A, int N){
	int i, j, k;
	double ratio;
	double det;
	double** triangle;
	triangle = (double**)malloc(N * sizeof(double*));
 
	for(i = 0; i < N; ++i){
        triangle[i] = (double*)malloc(N * sizeof(double));
    }
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; ++j){
			triangle[i][j] = (double)A[i][j];
		}
	}
	
	for(i = 0; i < N; ++i){
		printf("%lf\n", triangle[i][i]);
		if(triangle[i][i] == 0.0){
			return 0.0;
		}
		for (j = i + 1; j < N; ++j){
			ratio = (double)triangle[j][i] / (double)triangle[i][i];
			
			for(k = 0; k < N; ++k){
			  		triangle[j][k] = (double)triangle[j][k] - (double)ratio * (double)triangle[i][k];
				}
			}
	}
	 
	det = 1.0;
	for(i = 0; i < N; ++i){
        det = det * triangle[i][i];
    }
	
	for(i = 0; i < N; ++i){
        free(triangle[i]);
    }
    free(triangle);
    return det;
}

void Sum_Of_2_Matrix(float** A, float** B, float** C, int N, int M){
	int i, j;
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < M; ++j){
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	
}

void Prod_Of_2_Matrix(float** A, float** B, float** C, int N, int M, int Q){
	int i, j, k;
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < M; ++j){
			C[i][j] = 0;
		}
	}
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < M; ++j){
			for (k = 0; k < Q; ++k){
				C[i][j] += A[i][k] * B[k][j];
			}	
		}
	}
}

void Swap(float** A, int row1, int row2, int M){
	int i;
	float buff;
	
	for (i = 0; i < M; ++i){
		buff = A[row1][i];
		A[row1][i] = A[row2][i];
		A[row2][i] = buff;
	}
}

int Rank_Of_Matrix(float** A, int N, int M){
	float product;
	float** a;
	int rank, n, m, i, j;
	int flag;
	rank = M;
	
	a = dynamic_array_alloc(N, M);
	for (i = 0; i < N; ++i){
		for (j = 0; j < M; ++j){
			a[i][j] = A[i][j];
		}
	} 
	
	for (n = 0; n < rank; ++n){
		if (a[n][n] != 0){
			for (m = 0; m < N; ++m){
				if (m != n){
					product = (float)(a[m][n]) / (float)(a[n][n]);
					for (i = 0; i < rank; ++i){
						a[m][i] -= product * a[n][i];
					}
				}
			}
		}
		else{
			flag = 1;
			
			for (i = n + 1; i < N; ++i){
				if (a[i][n]){
					Swap(a, n, i, rank);
					flag = 0;
					break;
				}
			}

			if (flag == 1){
				rank--;
				
				for (i = 0; i < N; ++i)
					a[i][n] = a[i][rank];
			}
			n--;
		}
	}
	
	return rank;
}

float** ptrs_to_values(float* data, int N, int M){
	float** ret;
	int i, j;
	
	ret = dynamic_array_alloc(N, M);
	
	for (i = 0; i < N; ++i){
		for (j = 0; j < M; ++j){
			ret[i][j] = *(data + i * M + j);
		}
	}
	
	return ret;
	dynamic_array_free(ret, N);
}

double Determinant(double **A, int N){
    int i, j, j1, j2;
    double det;
    double** M;
    M = NULL;
    
    if (N < 1){
    	return 0;
	}
    else if (N == 1){
    		det = A[0][0];
        }
		else if (N == 2){
        	det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
        }
    	else{
        	det = 0.0;
        	for (j1 = 0; j1 < N; ++j1){
            	M = (double**)malloc((N - 1)* sizeof(double*));
				for (i = 0; i < N - 1; ++i){
					M[i] = (double*)malloc((N - 1) * sizeof(double));
				}
         		for (i = 1; i < N; ++i){
                	j2 = 0;
                	for (j = 0; j < N; ++j){
                    	if (j == j1){
							continue;
						}
                    	M[i - 1][j2] = A[i][j];
                    	j2++;
                	}
                }

            det += pow(-1.0, 1.0 + j1 + 1.0) * A[0][j1] * Determinant(M, N - 1);
            
			for (i = 0 ; i < N - 1; ++i){
            	free(M[i]);
			}
            free(M);
        }
    }
    
    return det;
}
