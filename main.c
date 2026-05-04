#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int rows;
    int cols;
    double **content;
    double **contentTraspose;
} MatrixStruct;

typedef struct {
    double X;
    double Y;
    double Z;
} VectorStruct;

typedef struct {
    int MatrixArrayLenght;
    int VectorArrayLenght;
    MatrixStruct **MatrixArray;
    VectorStruct *VectorArray;
} MatrixVectorStruct;

void options(MatrixVectorStruct *MatrixVectorArray);
void addMatrix(MatrixVectorStruct *MatrixVectorArray);
void addVector(MatrixVectorStruct *MatrixVectorArray);
void showAllMatrix(MatrixVectorStruct *MatrixVectorArray, char *type);
void showAllVectors(MatrixVectorStruct *MatrixVectorArray);
void showMatrix(MatrixStruct *Matrix, char *type, int Position);
void showVector(VectorStruct Vector, int Position);
void operations(MatrixVectorStruct *MatrixVectorArray);
void sumRestVectors(MatrixVectorStruct* MatrixVectorArray, char *OperationType);
int confirmVectors(VectorStruct Vector1, VectorStruct Vector2, int numVector1, int numVector2, char *OperationType);
int confirmQuestion(char *question);
void showErrors(int ErrorCode, char *Component);

int main() {
    MatrixVectorStruct *TempMatrixVectorArray = calloc(1, sizeof(*TempMatrixVectorArray));

    if (TempMatrixVectorArray == NULL) {
        showErrors(1, "estructura principal");
        return 1;
    }

    MatrixVectorStruct *MatrixVectorArray = TempMatrixVectorArray;

    MatrixStruct **TempMatrixArray = calloc(1, sizeof(*TempMatrixArray));

    if (TempMatrixArray == NULL) {
        showErrors(1, "arreglo de matrices");
        free(MatrixVectorArray);
        return 1;
    }

    MatrixVectorArray -> MatrixArray = TempMatrixArray;

    VectorStruct *TempVector = calloc(1, sizeof(*TempVector));

    if (TempVector == NULL) {
        showErrors(1, "arreglo de vectores");
        free(MatrixVectorArray -> MatrixArray);
        free(MatrixVectorArray);
        return 1;
    }

    MatrixVectorArray -> VectorArray = TempVector;
    MatrixVectorArray -> MatrixArrayLenght = 0;
    MatrixVectorArray -> VectorArrayLenght = 0;

    options(MatrixVectorArray);
}

void options(MatrixVectorStruct *MatrixVectorArray) {
    while (1) {
        int type; 

        printf("\n[!] Selecciona la opcion deseada: \n");
        printf("1.- Agregar Matriz\n");
        printf("2.- Agregar Vector\n");
        printf("3.- Ver opciones de operaciones\n");
        printf("4.- Mostrar matrices originales\n");
        printf("5.- Mostrar matrices traspuestas\n");
        printf("6.- Mostrar vectores\n");
        printf("7.- Salir\n");
        printf("--> ");
        scanf("%i", &type);

        switch (type)
        {
        case 1:
            addMatrix(MatrixVectorArray);
            break;
        
        case 2:
            addVector(MatrixVectorArray);
            break;

        case 3:
            operations(MatrixVectorArray);
            break;

        case 4:
            showAllMatrix(MatrixVectorArray, "originales");
            break;

        case 5:
            showAllMatrix(MatrixVectorArray, "traspuestas");
            break;

        case 6:
            showAllVectors(MatrixVectorArray);
            break;
        
        case 7:
            printf("\n\n [!] Gracias por usar el programa\n\n");
            
            exit(0);

        default:
            showErrors(5, "");
            break;
        };
    };
};

void addMatrix(MatrixVectorStruct *MatrixVectorArray) {
    // nuevo tamano temporal de array
    int TempArrayLenght = MatrixVectorArray -> MatrixArrayLenght + 1;
    // inicializacion de tamanos de matriz
    int NewMatrixRows = 0;
    int NewMatrixCols = 0;
    
    // creacion de componente para errores
    char Component[50];
    snprintf(Component, sizeof(Component), "matriz %d", TempArrayLenght);


    // agrandamiento temporal de array de matrices en una posicion
    MatrixStruct **TempMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * TempArrayLenght);

    
    if (TempMatrixArray == NULL) {
        showErrors(1, Component);
        return;
    };

    MatrixVectorArray -> MatrixArray = TempMatrixArray;

    while (NewMatrixRows <= 0) {
        printf("\n[*] Ingresa el numero de filas que contiene la matriz %d:\n", TempArrayLenght);
        printf("--> ");
        scanf("%d", &NewMatrixRows);

        if (NewMatrixRows <= 0) showErrors(2, "filas de matriz");
    };
    
    while (NewMatrixCols <= 0) {
        printf("\n[*] Ingresa el numero de columnas que contiene la matriz %d:\n", TempArrayLenght);
        printf("--> ");
        scanf("%d", &NewMatrixCols);

        if (NewMatrixCols <= 0) showErrors(2, "columnas de matriz");
    };
    
    MatrixStruct *TempMatrix = calloc(1, sizeof(*TempMatrix));

    if (TempMatrix == NULL) {
        showErrors(1, Component);
        return;
    }

    MatrixVectorArray -> MatrixArray[ MatrixVectorArray -> MatrixArrayLenght ] = TempMatrix;
    MatrixStruct *Matrix = MatrixVectorArray -> MatrixArray[ MatrixVectorArray -> MatrixArrayLenght ];
    
    Matrix -> rows = NewMatrixRows;
    Matrix -> cols = NewMatrixCols;
    
    double **TempContent = calloc(NewMatrixRows, sizeof(*TempContent));

    if (TempContent == NULL) {
        snprintf(Component, sizeof(Component), "contenido de matriz %d", TempArrayLenght);
        showErrors(1, Component);
        free(Matrix);

        if (MatrixVectorArray -> MatrixArrayLenght == 0) {
            free(MatrixVectorArray -> MatrixArray);
            MatrixVectorArray -> MatrixArray = NULL;
        } else {
            MatrixStruct **TempShrinkMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * MatrixVectorArray -> MatrixArrayLenght);

            if (TempShrinkMatrixArray != NULL) {
                MatrixVectorArray -> MatrixArray = TempShrinkMatrixArray;
            }
        }

        return;
    }

    Matrix -> content = TempContent;
    
    for (int row = 0; row < NewMatrixRows; row++) {
        double *TempRow = calloc(NewMatrixCols, sizeof(*TempRow));

        if (TempRow == NULL) {
            snprintf(Component, sizeof(Component), "fila de matriz %d", TempArrayLenght);
            showErrors(1, Component);

            for (int previousRow = 0; previousRow < row; previousRow++) {
                free(Matrix -> content[previousRow]);
            }

            free(Matrix -> content);
            free(Matrix);

            if (MatrixVectorArray -> MatrixArrayLenght == 0) {
                free(MatrixVectorArray -> MatrixArray);
                MatrixVectorArray -> MatrixArray = NULL;
            } else {
                MatrixStruct **TempShrinkMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * MatrixVectorArray -> MatrixArrayLenght);

                if (TempShrinkMatrixArray != NULL) {
                    MatrixVectorArray -> MatrixArray = TempShrinkMatrixArray;
                }
            }

            return;
        }

        Matrix -> content[row] = TempRow;

        for (int col = 0; col < NewMatrixCols; col++) {
            double Value = 0;
            printf("\n[#] Ingresa el valor de la fila %d, columna %d:\n", row + 1, col + 1);
            printf("--> ");
            scanf("%lf", &Value);
            Matrix -> content[row][col] = Value;
            printf("\n");
        };
    };
    
    double **TempContentTraspose = calloc(NewMatrixCols, sizeof(*TempContentTraspose));

    if (TempContentTraspose == NULL) {
        snprintf(Component, sizeof(Component), "contenido de matriz traspuesta %d", TempArrayLenght);
        showErrors(1, Component);

        for (int row = 0; row < NewMatrixRows; row++) {
            free(Matrix -> content[row]);
        }

        free(Matrix -> content);
        free(Matrix);

        if (MatrixVectorArray -> MatrixArrayLenght == 0) {
            free(MatrixVectorArray -> MatrixArray);
            MatrixVectorArray -> MatrixArray = NULL;
        } else {
            MatrixStruct **TempShrinkMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * MatrixVectorArray -> MatrixArrayLenght);

            if (TempShrinkMatrixArray != NULL) {
                MatrixVectorArray -> MatrixArray = TempShrinkMatrixArray;
            }
        }

        return;
    }

    Matrix -> contentTraspose = TempContentTraspose;
    
    for (int col = 0; col < NewMatrixCols; col++) {
        double *TempRowTraspose = calloc(NewMatrixRows, sizeof(*TempRowTraspose));

        if (TempRowTraspose == NULL) {
            snprintf(Component, sizeof(Component), "fila de matriz traspuesta %d", TempArrayLenght);
            showErrors(1, Component);

            for (int previousCol = 0; previousCol < col; previousCol++) {
                free(Matrix -> contentTraspose[previousCol]);
            }

            free(Matrix -> contentTraspose);

            for (int row = 0; row < NewMatrixRows; row++) {
                free(Matrix -> content[row]);
            }

            free(Matrix -> content);
            free(Matrix);

            if (MatrixVectorArray -> MatrixArrayLenght == 0) {
                free(MatrixVectorArray -> MatrixArray);
                MatrixVectorArray -> MatrixArray = NULL;
            } else {
                MatrixStruct **TempShrinkMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * MatrixVectorArray -> MatrixArrayLenght);

                if (TempShrinkMatrixArray != NULL) {
                    MatrixVectorArray -> MatrixArray = TempShrinkMatrixArray;
                }
            }

            return;
        }

        Matrix -> contentTraspose[col] = TempRowTraspose;

        for (int row = 0; row < NewMatrixRows; row++) {
            double Value = 0;
            Value = Matrix -> content[row][col];
            Matrix -> contentTraspose[col][row] = Value;
        }
    }

    MatrixVectorArray -> MatrixArrayLenght = TempArrayLenght;
    
    return;
};

void addVector(MatrixVectorStruct *MatrixVectorArray) {
    int TempArrayLenght = MatrixVectorArray -> VectorArrayLenght + 1;
    double x = 0;
    double y = 0;
    double z = 0;

    char Component[50];
    snprintf(Component, sizeof(Component), "vector %d", TempArrayLenght);
    
    printf("\n[*] Ingresa el valor de X:\n");
    printf("--> ");
    scanf("%lf", &x);
    
    printf("\n[*] Ingresa el valor de Y:\n");
    printf("--> ");
    scanf("%lf", &y);
    
    printf("\n[*] Ingresa el valor de Z:\n");
    printf("--> ");
    scanf("%lf", &z);

    if (x == 0 && y == 0 && z == 0) {
        showErrors(4, Component);
        return;
    }

    VectorStruct *TempVectorArray = realloc(MatrixVectorArray -> VectorArray, sizeof(*TempVectorArray) * TempArrayLenght);

    if (TempVectorArray == NULL) {
        showErrors(1, Component);
        free(TempVectorArray);
        return;
    }

    MatrixVectorArray -> VectorArray = TempVectorArray;
    VectorStruct *Vector = &MatrixVectorArray -> VectorArray[ TempArrayLenght - 1 ];
    MatrixVectorArray -> VectorArrayLenght = TempArrayLenght;

    Vector -> X = x;
    Vector -> Y = y;
    Vector -> Z = z;

    return;
}

void showAllMatrix(MatrixVectorStruct *MatrixVectorArray, char *type) {
    if (MatrixVectorArray -> MatrixArrayLenght == 0) {
        showErrors(3, "Matriz");
        return;
    }

    printf("\n--> Listado de matrices %s <--\n", type);

    for (int i = 0; i < MatrixVectorArray -> MatrixArrayLenght; i++) {
        MatrixStruct *Matrix = MatrixVectorArray -> MatrixArray[i];
        showMatrix(Matrix, type, i + 1);
    }
    printf("\n");
    return;
}

void showAllVectors(MatrixVectorStruct *MatrixVectorArray) {
    printf("\n--> Lista de vectores <--\n");
    for (int i = 0; i < MatrixVectorArray -> VectorArrayLenght; i++) {
        VectorStruct Vector = MatrixVectorArray -> VectorArray[i];
        showVector(Vector, i);
    }
    return;
}

void showMatrix(MatrixStruct *Matrix, char *type, int Position) {
        printf("\n[#] Matriz #%d\n\n", Position);
        int rows = strcmp(type, "originales") == 0 ? Matrix -> rows : Matrix -> cols;
        int cols = strcmp(type, "originales") == 0 ? Matrix -> cols : Matrix -> rows;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                double Value = strcmp(type, "originales") == 0 ? Matrix -> content[row][col] : Matrix -> contentTraspose[row][col];
                
                int absValue = fabs(Value);
                char *Spaces;
                if (absValue >= 1000) {
                    Spaces = "";
                } else if (absValue >= 100) {
                    Spaces = " ";
                } else if (absValue >= 10) {
                    Spaces = "  ";
                } else {
                    Spaces = "   ";
                }

                printf("%s%.2lf ", Spaces, Value);
            }
            printf("\n");
        }
}

void showVector(VectorStruct Vector, int Position) {
        char XValue[10];
        char YValue[10];
        char ZValue[10];

        if (Vector.X != 0) {
            snprintf(XValue, sizeof(XValue), "%.2lfX, ", Vector.X);
        } else XValue[0] = '\0';
        
        if (Vector.Y != 0) {
            snprintf(YValue, sizeof(YValue), "%.2lfY, ", Vector.Y);
        } else YValue[0] = '\0';
        
        if (Vector.Z != 0) {
            snprintf(ZValue, sizeof(ZValue), "%.2lfZ", Vector.Z);
        } else ZValue[0] = '\0';

        if (Position >= 0) printf("\n[#] Vector %d\n", Position + 1);
        printf("( %s%s%s )\n", XValue, YValue, ZValue);
        return;
}

void operations(MatrixVectorStruct *MatrixVectorArray) {

    int option;
    
    while(1) {
        printf("\n[!] Ingresa el tipo de operacion que deseas hacer:\n");
        printf("0.-  Regresar al menu\n");
        printf("--> Matrices <--\n");
        printf("1.- Suma de matrices\n");
        printf("2.- Resta de matrices\n");
        printf("3.- Multiplicacion de matrices\n");
        printf("4.- Multiplicacion por escalar\n");
        printf("5.- Identificar tipo de relacion en matriz binaria\n");
        printf("--> Vectores <--\n");
        printf("6.- Suma de vectores\n");
        printf("7.- Resta de vectores\n");
        printf("8.- Producto punto\n");
        printf("9.- Producto cruz\n");
        printf("--> ");
        scanf("%i", &option);

        if (option >= 0 && option <= 9) {
            break;
        } else showErrors(5, "");
    }

    switch (option) {
        case 0:
            break;

        case 6:
            sumRestVectors(MatrixVectorArray, "suma");
            break;
        
        case 7: 
            sumRestVectors(MatrixVectorArray, "resta");
            break;

        default:
            break;
    }
    return;
}

void sumRestVectors(MatrixVectorStruct* MatrixVectorArray, char *OperationType) {
    if (MatrixVectorArray -> VectorArrayLenght == 0) {
        showErrors(3, "vectores");
        return;
    }

    int numVector1;
    int numVector2;
    VectorStruct Vector1;
    VectorStruct Vector2;
    VectorStruct resVector;

    while(1) {
        int confirm;

        printf("\n[*] Ingresa el numero de vector 1 a sumar:\n");
        printf("--> ");
        scanf("%d", &numVector1);
    
        printf("\n[*] Ingresa el numero de vector 2 a sumar:\n");
        printf("--> ");
        scanf("%d", &numVector2);

        numVector1 -= 1;
        numVector2 -= 1;

        Vector1 = MatrixVectorArray -> VectorArray[numVector1];
        Vector2 = MatrixVectorArray -> VectorArray[numVector2];

        confirm = confirmVectors(Vector1, Vector2, numVector1, numVector2, OperationType);

        if (confirm) break;
    }

    if (strcmp(OperationType, "suma") == 0) {
        resVector.X = Vector1.X + Vector2.X;
        resVector.Y = Vector1.Y + Vector2.Y;
        resVector.Z = Vector1.Z + Vector2.Z;
    } else {
        resVector.X = Vector1.X - Vector2.X;
        resVector.Y = Vector1.Y - Vector2.Y;
        resVector.Z = Vector1.Z - Vector2.Z;
    }

    printf("\n[*] Vector resultante:\n");
    showVector(resVector, -1);

    int confirm = confirmQuestion("Deseas agregar el vector resultante a la lista de vectores?");
    if (confirm) {
        char Component[90];
        int tempVectorArrayLenght = MatrixVectorArray -> VectorArrayLenght + 1;
        snprintf(Component, sizeof(Component), "vector resultante de %s entre vector #%d y #%d en la posicion del array #%d", 
            OperationType, numVector1, numVector2, tempVectorArrayLenght);

        VectorStruct *tempVectorArray = realloc(MatrixVectorArray -> VectorArray, sizeof(VectorStruct) * tempVectorArrayLenght);

        if (tempVectorArray == NULL) {
            showErrors(1, Component);
            free(tempVectorArray);
            return;
        }

        MatrixVectorArray -> VectorArray = tempVectorArray;
        MatrixVectorArray -> VectorArray[tempVectorArrayLenght - 1] = resVector;
        MatrixVectorArray -> VectorArrayLenght = tempVectorArrayLenght;

        printf("\n[*] Vector almacenado correctamente en la posicion #%d\n\n", tempVectorArrayLenght);
    }

    return;
}

int confirmVectors(VectorStruct Vector1, VectorStruct Vector2, int numVector1, int numVector2, char *OperationType) {
    int confirm;
    
    printf("\n[!] Confirma los vectores a %s:\n", OperationType);
        
    showVector(Vector1, numVector1);
    showVector(Vector2, numVector2);

    confirm = confirmQuestion("Son correctos?");
    return confirm;
}

int confirmQuestion(char *question) {
    int option;
    while(1) {
        printf("\n[?] %s\n", question);
        printf("1.- Si\n");
        printf("2.- No\n");
        printf("--> ");
        scanf("%d", &option);
        
        if (option == 1) {
            return 1;
        } else if (option == 2) {
            return 0;
        } else {
            showErrors(5, "");
        }
    }
}

void showErrors(int ErrorCode, char *Component) {
    printf("\n");
    switch(ErrorCode) {
        case 1:
            printf("[!] Error 1 (memoryError): Reserva de memoria en %s fallida.", Component);
            break;
        case 2:
            printf("[!] Error 2 (lessThan0Value): Valor menor o igual a 0 ingresado en %s.", Component);
            break;
        case 3:
            printf("[!] Error 3 (emptyArray): No hay %s para operar.", Component);
            break;
        case 4:
            printf("[!] Error 4 (nullVector): El %s ingresado es nulo.", Component);
            break;
        case 5:
            printf("[!] Error 5 (wrongValue): El valor ingresado es incorrecto");
            break;
        default: 
            printf("[!] Error desconocido en componente %s.", Component);
    }
    printf("\n\n");
    return;
}