#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int rows;
    int cols;
    int trasposeRows;
    int trasposeCols;
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

int setMatrixVectorArray();
void options();
void addMatrix();
int makeMatrixArrayBigger(int TempArrayLenght, char* Component);
int getTrasposeMatrix(MatrixStruct *Matrix, int NewMatrixRows, int NewMatrixCols, int TempArrayLenght);
void addVector();
void showAllMatrix(char *type);
void showAllVectors();
void showMatrix(MatrixStruct *Matrix, char *type, int Position, int isBinarial);
void showVector(VectorStruct Vector, int Position);
void operations();
char **selectMatrixType(int numOfElements);
void sumRestMatrix(char *OperationType);
void multMatrixMatrix();
void multEscalarMatrix();
void identifyMatrixRelations();
int binarialMatrixValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols);
int reflexiveValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols);
int *symmetricValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols);
int transitiveValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols);
void addExistMatrixToArray(MatrixStruct *Matrix, int TempArrayLenght);
double getRowColMatrixValue(MatrixStruct *Matrix, char *MatrixType, int row, int col);
MatrixStruct *getMatrix(char* matrixType, char *OperationType, int isBinarial);
MatrixStruct **getMatrixArray(char *OperationType, char** matrixTypes);
int confirmMatrix(MatrixStruct *Matrix, int numMatrix, char *MatrixType, int isBinarial);
int confirmMatrixArray(MatrixStruct *Matrix1, int numMatrix1, char *MatrixType1, MatrixStruct *Matrix2, 
        int numMatrix2, char *MatrixType2,char *OperationType);
void sumRestVectors(char *OperationType);
void pointProduct();
void crossProduct();
void addExistVectorToArray(char *OperationType, VectorStruct Vector);
int *selectElements(char *variableType, int numElements, char **variables, char *OperationType);
int confirmVectors(VectorStruct Vector1, VectorStruct Vector2, int numVector1, int numVector2, char *OperationType);
int confirmQuestion(char *question);
void showErrors(int ErrorCode, char *Component);

MatrixVectorStruct *MatrixVectorArray;

int main() {
    if (!setMatrixVectorArray()) return 1;
    options();
}

int setMatrixVectorArray() {
    // creacion de estructura principal para almacenar matrices y vectores
    MatrixVectorStruct *TempMatrixVectorArray = calloc(1, sizeof(*TempMatrixVectorArray));

    if (TempMatrixVectorArray == NULL) {
        showErrors(1, "estructura principal");
        return 0;
    }
    // asignacion de memoria reservada al apuntador global
    MatrixVectorArray = TempMatrixVectorArray;

    // creacion inicial del arreglo dinamico de matrices
    MatrixStruct **TempMatrixArray = calloc(1, sizeof(*TempMatrixArray));

    if (TempMatrixArray == NULL) {
        showErrors(1, "arreglo de matrices");
        free(MatrixVectorArray);
        return 0;
    }
    MatrixVectorArray -> MatrixArray = TempMatrixArray;

    // creacion inicial del arreglo dinamico de vectores
    VectorStruct *TempVector = calloc(1, sizeof(*TempVector));

    if (TempVector == NULL) {
        showErrors(1, "arreglo de vectores");
        free(MatrixVectorArray -> MatrixArray);
        free(MatrixVectorArray);
        return 0;
    }
    // inicializacion de apuntadores y tamanos de arreglos
    MatrixVectorArray -> VectorArray = TempVector;
    MatrixVectorArray -> MatrixArrayLenght = 0;
    MatrixVectorArray -> VectorArrayLenght = 0;
    return 1;
}

void options() {
    // ciclo principal del menu hasta que el usuario decida salir
    while (1) {
        int type; 

        // impresion de opciones principales del programa
        printf("\n [!] Selecciona la opcion deseada: \n");
        printf(" 1.- Agregar Matriz\n");
        printf(" 2.- Agregar Vector\n");
        printf(" 3.- Ver opciones de operaciones\n");
        printf(" 4.- Mostrar matrices originales\n");
        printf(" 5.- Mostrar matrices traspuestas\n");
        printf(" 6.- Mostrar vectores\n");
        printf(" 7.- Salir\n");
        printf(" --> ");
        scanf("%i", &type);

        switch (type)
        {
        case 1:
            addMatrix();
            break;
        
        case 2:
            addVector();
            break;

        case 3:
            operations();
            break;

        case 4:
            showAllMatrix("originales");
            break;

        case 5:
            showAllMatrix("traspuestas");
            break;

        case 6:
            showAllVectors();
            break;
        
        case 7:
            printf("\n\n[!] Gracias por usar el programa\n\n");
            exit(0);

        default:
            showErrors(5, "");
            break;
        };
    };
};

void addMatrix() {
    // nuevo tamano temporal de array
    int TempArrayLenght = MatrixVectorArray -> MatrixArrayLenght + 1;
    // inicializacion de tamanos de matriz
    int NewMatrixRows = 0;
    int NewMatrixCols = 0;

    int confirmation = 0;
    
    // creacion de componente para errores
    char Component[50];
    snprintf(Component, sizeof(Component), "matriz %d", TempArrayLenght);


    // agrandamiento temporal de array de matrices en una posicion
    if (!makeMatrixArrayBigger(TempArrayLenght, Component)) return;

    while (NewMatrixRows <= 0) {
        printf("\n [*] Ingresa el numero de filas que contiene la matriz %d:\n", TempArrayLenght);
        printf(" --> ");
        scanf("%d", &NewMatrixRows);

        if (NewMatrixRows <= 0) showErrors(2, "filas de matriz");
    };
    
    while (NewMatrixCols <= 0) {
        printf("\n [*] Ingresa el numero de columnas que contiene la matriz %d:\n", TempArrayLenght);
        printf(" --> ");
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
    Matrix -> trasposeRows = NewMatrixCols;
    Matrix -> trasposeCols = NewMatrixRows;
    
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
            printf("\n [#] Ingresa el valor de la fila %d, columna %d:\n", row + 1, col + 1);
            printf(" --> ");
            scanf("%lf", &Value);
            Matrix -> content[row][col] = Value;
            printf("\n");
        };
    };
    
    confirmation = getTrasposeMatrix(Matrix, NewMatrixRows, NewMatrixCols, TempArrayLenght);

    if (confirmation) MatrixVectorArray -> MatrixArrayLenght = TempArrayLenght;
    
    return;
};

int makeMatrixArrayBigger(int TempArrayLenght, char* Component) {
    // redimensionamiento del arreglo de matrices al nuevo tamano temporal
    MatrixStruct **TempMatrixArray = realloc(MatrixVectorArray -> MatrixArray, sizeof(MatrixStruct *) * TempArrayLenght);

    
    if (TempMatrixArray == NULL) {
        showErrors(1, Component);
        return 0;
    };

    MatrixVectorArray -> MatrixArray = TempMatrixArray;
    return 1;
}

int getTrasposeMatrix(MatrixStruct *Matrix, int NewMatrixRows, int NewMatrixCols, int TempArrayLenght) {
    // creacion de componente para errores de matriz traspuesta
    char Component[50];
    // reserva de memoria para el contenido de la matriz traspuesta
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

        return 0;
    }
    Matrix -> contentTraspose = TempContentTraspose;
    
    // llenado de la matriz traspuesta intercambiando filas por columnas
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

            return 0;
        }

        Matrix -> contentTraspose[col] = TempRowTraspose;

        for (int row = 0; row < NewMatrixRows; row++) {
            double Value = 0;
            Value = Matrix -> content[row][col];
            Matrix -> contentTraspose[col][row] = Value;
        }
    }
    return 1;
}

void addVector() {
    // nuevo tamano temporal del arreglo de vectores
    int TempArrayLenght = MatrixVectorArray -> VectorArrayLenght + 1;
    double x = 0;
    double y = 0;
    double z = 0;

    // creacion de componente para errores
    char Component[50];
    snprintf(Component, sizeof(Component), "vector %d", TempArrayLenght);
    
    // solicitud de componentes del vector
    printf("\n [*] Ingresa el valor de X:\n");
    printf(" --> ");
    scanf("%lf", &x);
    
    printf("\n [*] Ingresa el valor de Y:\n");
    printf(" --> ");
    scanf("%lf", &y);
    
    printf("\n [*] Ingresa el valor de Z:\n");
    printf(" --> ");
    scanf("%lf", &z);

    // validacion para evitar almacenar un vector nulo
    if (x == 0 && y == 0 && z == 0) {
        showErrors(4, Component);
        return;
    }

    // agrandamiento temporal del arreglo de vectores
    VectorStruct *TempVectorArray = realloc(MatrixVectorArray -> VectorArray, sizeof(*TempVectorArray) * TempArrayLenght);

    if (TempVectorArray == NULL) {
        showErrors(1, Component);
        free(TempVectorArray);
        return;
    }

    MatrixVectorArray -> VectorArray = TempVectorArray;
    VectorStruct *Vector = &MatrixVectorArray -> VectorArray[ TempArrayLenght - 1 ];
    MatrixVectorArray -> VectorArrayLenght = TempArrayLenght;

    // asignacion de valores al nuevo vector
    Vector -> X = x;
    Vector -> Y = y;
    Vector -> Z = z;

    return;
}

void showAllMatrix(char *type) {
    // validacion de existencia de matrices antes de mostrarlas
    if (MatrixVectorArray -> MatrixArrayLenght == 0) {
        showErrors(3, "Matriz");
        return;
    }

    printf("\n --> Listado de matrices %s <--\n", type);

    // recorrido del arreglo de matrices para imprimir cada una
    for (int i = 0; i < MatrixVectorArray -> MatrixArrayLenght; i++) {
        MatrixStruct *Matrix = MatrixVectorArray -> MatrixArray[i];
        showMatrix(Matrix, type, i, 0);
    }
    printf("\n");
    return;
}

void showAllVectors() {
    // impresion de todos los vectores almacenados
    printf("\n --> Lista de vectores <--\n");
    for (int i = 0; i < MatrixVectorArray -> VectorArrayLenght; i++) {
        VectorStruct Vector = MatrixVectorArray -> VectorArray[i];
        showVector(Vector, i);
    }
    return;
}

void showMatrix(MatrixStruct *Matrix, char *type, int Position, int isBinarial) {
        // impresion opcional del numero de matriz
        if (Position >= 0) printf("\n[#] Matriz #%d\n\n", Position + 1);
        // seleccion de dimensiones segun si la matriz es original o traspuesta
        int rows = strcmp(type, "originales") == 0 ? Matrix -> rows : Matrix -> cols;
        int cols = strcmp(type, "originales") == 0 ? Matrix -> cols : Matrix -> rows;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                // seleccion del valor a imprimir segun el tipo de matriz
                double Value = strcmp(type, "originales") == 0 ? Matrix -> content[row][col] : Matrix -> contentTraspose[row][col];
                
                // calculo de espacios para alinear visualmente la matriz
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

                if (isBinarial) {
                    printf("%s%.0lf ", Spaces, Value);
                } else printf("%s%.2lf ", Spaces, Value);
            }
            printf("\n");
        }
}

void showVector(VectorStruct Vector, int Position) {
        // cadenas temporales para imprimir solo componentes no nulas
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

void operations() {
    // ciclo del menu de operaciones hasta regresar al menu principal
    int option;
    
    while(1) {
        printf("\n [!] Ingresa el tipo de operacion que deseas hacer:\n");
        printf(" 0.-  Regresar al menu\n");
        printf(" --> Matrices <--\n");
        printf(" 1.- Suma de matrices\n");
        printf(" 2.- Resta de matrices\n");
        printf(" 3.- Multiplicacion de matrices\n");
        printf(" 4.- Multiplicacion por escalar\n");
        printf(" 5.- Identificar tipo de relacion en matriz binaria\n");
        printf(" --> Vectores <--\n");
        printf(" 6.- Suma de vectores\n");
        printf(" 7.- Resta de vectores\n");
        printf(" 8.- Producto punto\n");
        printf(" 9.- Producto cruz\n");
        printf(" --> ");
        scanf("%i", &option);

        switch (option) {
            case 0:
                return;

            case 1:
                sumRestMatrix("sumar");
                break;

            case 2:
                sumRestMatrix("restar");
                break;

            case 3:
                multMatrixMatrix();
                break;
            
            case 4:
                multEscalarMatrix();
                break;

            case 5:
                identifyMatrixRelations();
                break;

            case 6:
                sumRestVectors("sumar");
                break;
            
            case 7: 
                sumRestVectors("restar");
                break;

            case 8:
                pointProduct();
                break;

            case 9:
                crossProduct();
                break;

            default:
                showErrors(5, "");
                break;
        }
    }
}

char **selectMatrixType(int numOfElements) {
    // arreglo temporal para almacenar si cada matriz sera original o traspuesta
    char **matrixTypes = calloc(numOfElements, sizeof(*matrixTypes));

    // seleccion del tipo de matriz para cada elemento solicitado
    for (int i = 0; i < numOfElements; i++) {
        int continueIterations = 0;
        while(!continueIterations) {
            int selection;

            printf("\n [!] Selecciona el tipo de matriz %d:\n", i);
            printf(" 1.- Originales\n");
            printf(" 2.- Traspuesta\n");
            printf(" --> ");
            scanf("%d", &selection);

            switch (selection) {
            case 1:
                matrixTypes[i] = "originales";
                continueIterations = 1;
                break;

            case 2:
                matrixTypes[i] = "traspuestas";
                continueIterations = 1;
                break;
            
            default:
                showErrors(5, "");
                break;
            }
        }
    }

    return matrixTypes;
}

void sumRestMatrix(char *OperationType) {
    // nuevo tamano temporal del arreglo de matrices para guardar el resultado
    int TempArrayLenght = MatrixVectorArray -> MatrixArrayLenght + 1;
    int Operationfactor = 0;

    // seleccion de tipos y matrices a operar
    char **matrixTypes = selectMatrixType(2);
    MatrixStruct **MatrixArray = getMatrixArray(OperationType, matrixTypes);
    
    // validacion de dimensiones compatibles para suma o resta
    if (MatrixArray[0] -> cols != MatrixArray[1] -> cols || MatrixArray[0] -> rows != MatrixArray[1] -> rows) {
        showErrors(6, "");
        return;
    }

    // definicion del signo de operacion segun suma o resta
    Operationfactor = (strcmp(OperationType, "sumar") == 0) ? 1 : -1;

    int rows = MatrixArray[0] -> rows;
    int cols = MatrixArray[0] -> cols;
    
    // addMemoryValidation
    MatrixStruct *resMatrix = calloc(1, sizeof(*resMatrix));
    resMatrix -> content = calloc(rows, sizeof(double*));
    resMatrix -> rows = rows;
    resMatrix -> cols = cols;

    // calculo de cada celda de la matriz resultante
    for (int row = 0; row < rows; row++) {
        resMatrix -> content[row] = calloc(cols, sizeof(double));
        for (int col = 0; col < cols; col++) {
            resMatrix -> content[row][col] = getRowColMatrixValue(MatrixArray[0], matrixTypes[0], row, col) + 
                                             getRowColMatrixValue(MatrixArray[1], matrixTypes[1], row, col) * Operationfactor;
        }
    }
    getTrasposeMatrix(resMatrix, rows, cols, TempArrayLenght);
    addExistMatrixToArray(resMatrix, TempArrayLenght);
    return;
}

void multMatrixMatrix() {
    // nuevo tamano temporal del arreglo de matrices para guardar el resultado
    int TempArrayLenght = MatrixVectorArray -> MatrixArrayLenght + 1;
    // seleccion de tipos y matrices a multiplicar
    char **matrixTypes = selectMatrixType(2);
    MatrixStruct **MatrixArray = getMatrixArray("multiplicacion de matrices", matrixTypes);
    
    // obtencion de dimensiones necesarias para validar multiplicacion
    int verificationRows = (strcmp("originales", matrixTypes[0]) == 0) ? MatrixArray[1] -> rows : MatrixArray[1] -> trasposeRows;
    int verificationCols = (strcmp("originales", matrixTypes[1]) == 0) ? MatrixArray[0] -> cols : MatrixArray[0] -> trasposeCols;

    // validacion de compatibilidad entre columnas de la primera y filas de la segunda
    if (verificationRows != verificationCols) {
        showErrors(6, "");
        return;
    }

    MatrixStruct *resMatrix = calloc(1, sizeof(*resMatrix));

    // definicion de dimensiones de la matriz resultante
    int rows = (strcmp("originales", matrixTypes[0]) == 0) ? MatrixArray[0] -> rows : MatrixArray[0] -> trasposeRows;
    int cols = (strcmp("originales", matrixTypes[1]) == 0) ? MatrixArray[1] -> cols : MatrixArray[1] -> trasposeCols;

    resMatrix -> rows = rows;
    resMatrix -> cols = cols;
    resMatrix -> trasposeRows = cols;
    resMatrix -> trasposeCols = rows;

    resMatrix -> content = calloc(rows, sizeof(double*));

    // calculo de producto matriz por matriz
    for (int row = 0; row < rows; row++) {
        resMatrix -> content[row] = calloc(cols, sizeof(double));
        for (int col = 0; col < cols; col++) {
            double value = 0;
            for (int i = 0; i < MatrixArray[0] -> cols; i++) {
                value += getRowColMatrixValue(MatrixArray[0], matrixTypes[0], row, i) * 
                         getRowColMatrixValue(MatrixArray[1], matrixTypes[1], i, col);
            }
            resMatrix -> content[row][col] = value;
        }
    }
    getTrasposeMatrix(resMatrix, rows, cols, TempArrayLenght);
    addExistMatrixToArray(resMatrix, TempArrayLenght);
    return;
}

void multEscalarMatrix() {
    // nuevo tamano temporal del arreglo de matrices para guardar el resultado
    int TempArrayLenght = MatrixVectorArray -> MatrixArrayLenght + 1;
    // seleccion del tipo de matriz a multiplicar por escalar
    char *matrixType = selectMatrixType(1)[0];
    
    MatrixStruct *Matrix = getMatrix(matrixType, "escalar por matriz", 0);
    MatrixStruct *resMatrix = calloc(1, sizeof(*resMatrix));
    
    // solicitud del escalar multiplicador
    double factor;
    printf("\n [*] Ingresa el valor a multiplicar por la matriz\n");
    printf(" --> ");
    scanf("%lf", &factor);

    // definicion de dimensiones segun matriz original o traspuesta
    int rows = (strcmp("originales", matrixType) == 0) ? Matrix -> rows : Matrix -> trasposeRows;
    int cols = (strcmp("originales", matrixType) == 0) ? Matrix -> cols : Matrix -> trasposeCols;

    resMatrix -> rows = rows;
    resMatrix -> cols = cols;
    resMatrix -> trasposeRows = cols;
    resMatrix -> trasposeCols = rows;

    resMatrix -> content = calloc(rows, sizeof(double*));

    // multiplicacion de cada celda por el escalar ingresado
    for (int row = 0; row < rows; row++) {
        resMatrix -> content[row] = calloc(cols, sizeof(double));
        for (int col = 0; col < cols; col++) {
            resMatrix -> content[row][col] = getRowColMatrixValue(Matrix, matrixType, row, col) * factor;
        }
    }
    getTrasposeMatrix(resMatrix, rows, cols, TempArrayLenght);
    addExistMatrixToArray(resMatrix, TempArrayLenght);
    return;
}

void identifyMatrixRelations() {
    // seleccion de matriz para analizar relaciones binarias
    char *matrixType = selectMatrixType(1)[0];
    MatrixStruct *Matrix = getMatrix(matrixType, "relacion de matriz binaria", 1);

    // obtencion de dimensiones segun tipo de matriz seleccionado
    int rows = (strcmp("originales", matrixType) == 0) ? Matrix -> rows : Matrix -> trasposeRows;
    int cols = (strcmp("originales", matrixType) == 0) ? Matrix -> cols : Matrix -> trasposeCols;

    // validacion de que la matriz sea cuadrada y binaria
    if (!binarialMatrixValidation(Matrix, matrixType, rows, cols)) return;

    // evaluacion de propiedades de relacion binaria
    int isReflexive = reflexiveValidation(Matrix, matrixType, rows, cols);
    int *symmetricRelations = symmetricValidation(Matrix, matrixType, rows, cols);
    int isTransitive = transitiveValidation(Matrix, matrixType, rows, cols);

    // impresion de relaciones encontradas
    printf("\n --> Relaciones de la matriz binaria <--\n");
    if (isReflexive) printf(" [+] Reflexiva\n");
    if (symmetricRelations[0]) printf(" [+] Simetrica\n");
    if (symmetricRelations[1]) printf(" [+] Asimetrica\n");
    if (isTransitive) printf(" [+] Transitiva");
    if (!isReflexive && !symmetricRelations[0] && !symmetricRelations[1] && !isTransitive) printf(" [!] No hay relaciones\n");
    printf("\n");

    return;
}

int binarialMatrixValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols) {
    // validacion de matriz cuadrada
    if (rows != cols) {
        showErrors(6, "");
        return 0;
    }

    // validacion de que todos los valores sean 0 o 1
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            double value = getRowColMatrixValue(Matrix, matrixType, row, col);
            if (value != 0 && value != 1) {
                showErrors(7, "");
                return 0;
            }
        }
    }

    return 1;
}

int reflexiveValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols) {
    // una relacion es reflexiva si toda la diagonal principal contiene 1
    for (int row = 0; row < rows; row++) {
        if (getRowColMatrixValue(Matrix, matrixType, row, row) != 1) return 0;
    }
    return 1;
}

int *symmetricValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols) {
    // contadores para evaluar simetria y asimetria
    int maxIterations = rows * cols;
    int symmetricIteration = 0;
    int asymmetricIteration = 0;
    int *results = calloc(2, sizeof(int));

    // comparacion de cada posicion [i][j] con su posicion inversa [j][i]
    for (int row = 0; row < rows; row++) {
        for (int col =0; col < cols; col++) {
            double value1 = getRowColMatrixValue(Matrix, matrixType, row, col);
            double value2 = getRowColMatrixValue(Matrix, matrixType, col, row);
            if (value1 == 1 && value2 == 1) {
                symmetricIteration += 1;
            } else {
                asymmetricIteration += 1;
            };
        }
    }

    // almacenamiento de resultados: [0] simetrica, [1] asimetrica
    results[0] = (symmetricIteration == maxIterations) ? 1 : 0;
    results[1] = (asymmetricIteration == maxIterations) ? 1 : 0;

    return results;
}

int transitiveValidation(MatrixStruct *Matrix, char* matrixType, int rows, int cols) {
    // validacion de transitividad: si i se relaciona con j y j con k, entonces i debe relacionarse con k
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double value1 = getRowColMatrixValue(Matrix, matrixType, i, j);
            for (int k = 0; k < cols; k++) {
                double value2 = getRowColMatrixValue(Matrix, matrixType, j, k);
                if (value1 == 1 && value2 == 1) {
                    double value3 = getRowColMatrixValue(Matrix, matrixType, i, k);
                    if (value3 != 1) return 0;
                }
            }
        }
    }
    return 1;
}

void addExistMatrixToArray(MatrixStruct *Matrix, int TempArrayLenght) {
    // creacion de componente para errores
    char Component[50];
    snprintf(Component, sizeof(Component), "matriz %d", TempArrayLenght);

    // impresion de la matriz resultante antes de preguntar si se guarda
    printf("\n [*] Matriz resultante:\n");
    showMatrix(Matrix, "originales", -1, 0);

    // almacenamiento opcional de la matriz resultante
    int confirm = confirmQuestion("Deseas agregar el vector resultante a la lista de vectores?");
    if (confirm) {
        makeMatrixArrayBigger(TempArrayLenght, Component);
        MatrixVectorArray -> MatrixArray[TempArrayLenght - 1] = Matrix;
        MatrixVectorArray -> MatrixArrayLenght = TempArrayLenght;

        printf("\n [*] Matriz almacenada correctamente en la posicion #%d\n", TempArrayLenght);
    }
    return;
}

double getRowColMatrixValue(MatrixStruct *Matrix, char *MatrixType, int row, int col) {
    // obtencion de valor segun matriz original o traspuesta
    if (strcmp(MatrixType, "originales") == 0) {
        return Matrix -> content[row][col];
    } else {
        return Matrix -> contentTraspose[row][col];
    }
}

MatrixStruct *getMatrix(char* matrixType, char *OperationType, int isBinarial) {
    // seleccion y confirmacion de una sola matriz
    int elementSelected;
    int confirm = 0;
    MatrixStruct *Matrix;

    // arreglo auxiliar para reutilizar la funcion de seleccion de elementos
    char **matrixTypeArray = calloc(1, sizeof(char*));
    matrixTypeArray[0] = matrixType;
    
    // repeticion hasta que el usuario confirme la matriz correcta
    while (!confirm) {
        elementSelected = selectElements("matrices", 1, matrixTypeArray, OperationType)[0];

        Matrix = MatrixVectorArray -> MatrixArray[elementSelected];

        confirm = confirmMatrix(Matrix, elementSelected, matrixType, isBinarial);
    }

    return Matrix;
}

MatrixStruct **getMatrixArray(char *OperationType, char** matrixTypes) {
    // seleccion y confirmacion de dos matrices
    int confirm = 0;
    int *elementsSelected = calloc(2, sizeof(*elementsSelected));

    MatrixStruct **MatrixArray = calloc(2, sizeof(*MatrixArray));

    // repeticion hasta que el usuario confirme las matrices correctas
    while(!confirm) {
        elementsSelected = selectElements("matrices", 2, matrixTypes, OperationType);
        for (int i = 0; i < 2; i++) {
            MatrixArray[i] = MatrixVectorArray -> MatrixArray[elementsSelected[i]];
        }
        confirm = confirmMatrixArray(MatrixArray[0], elementsSelected[0], matrixTypes[0], MatrixArray[1], 
            elementsSelected[1], matrixTypes[1], OperationType);
    }
    return MatrixArray;
}

int confirmMatrix(MatrixStruct *Matrix, int numMatrix, char *MatrixType, int isBinarial) {
    // confirmacion visual de una matriz seleccionada
    int confirm;
    
    printf("\n [!] Confirma la matriz a operar:\n");

    showMatrix(Matrix, MatrixType, numMatrix, isBinarial);

    confirm = confirmQuestion("Es correcta?");
    return confirm;
}

int confirmMatrixArray(MatrixStruct *Matrix1, int numMatrix1, char *MatrixType1, MatrixStruct *Matrix2, 
        int numMatrix2, char *MatrixType2,char *OperationType) {
    
    // confirmacion visual de dos matrices seleccionadas
    int confirm;
    
    printf("\n [!] Confirma las matrices a %s:\n", OperationType);
        
    showMatrix(Matrix1, MatrixType1, numMatrix1, 0);
    showMatrix(Matrix2, MatrixType2, numMatrix2, 0);

    confirm = confirmQuestion("Son correctas?");
    return confirm;
}

void sumRestVectors(char *OperationType) {
    // etiquetas para solicitar los dos vectores a operar
    char **vectorTypes = calloc(2, sizeof(char*));
    vectorTypes[0] = "vector 1";
    vectorTypes[1] = "vector 2";

    // validacion de existencia de vectores antes de operar
    if (MatrixVectorArray -> VectorArrayLenght == 0) {
        showErrors(3, "vectores");
        return;
    }

    int confirm = 0;
    int *numVectorSelected;
    int operationFactor = 0;
    VectorStruct Vector1;
    VectorStruct Vector2;
    VectorStruct resVector;

    // seleccion y confirmacion de vectores a operar
    while(!confirm) {
        numVectorSelected = selectElements("vectores", 2, vectorTypes, OperationType);

        Vector1 = MatrixVectorArray -> VectorArray[numVectorSelected[0]];
        Vector2 = MatrixVectorArray -> VectorArray[numVectorSelected[1]];

        confirm = confirmVectors(Vector1, Vector2, numVectorSelected[0], numVectorSelected[1], OperationType);
    }

    // definicion del signo de operacion segun suma o resta
    operationFactor = (strcmp(OperationType, "sumar") == 0) ? 1 : -1;

    // calculo del vector resultante componente por componente
    resVector.X = Vector1.X + Vector2.X * operationFactor;
    resVector.Y = Vector1.Y + Vector2.Y * operationFactor;
    resVector.Z = Vector1.Z + Vector2.Z * operationFactor;
    
    addExistVectorToArray(OperationType, resVector);
    return;
}

void pointProduct() {
    // seleccion y confirmacion de vectores para producto punto
    int confirm = 0;
    int *numVectorSelected;
    char *OperationType = "producto punto";
    char **vectorTypes = calloc(2, sizeof(char*));
    vectorTypes[0] = "vector 1";
    vectorTypes[1] = "vector 2";

    VectorStruct vector1;
    VectorStruct vector2;
    double xResult;
    double yResult;
    double zResult;
    double pointProductResult;

    // repeticion hasta confirmar los vectores correctos
    while (!confirm) {
        numVectorSelected = selectElements("vectores", 2, vectorTypes, OperationType);
        vector1 = MatrixVectorArray -> VectorArray[numVectorSelected[0]]; 
        vector2 = MatrixVectorArray -> VectorArray[numVectorSelected[1]]; 
        confirm = confirmVectors(vector1, vector2, numVectorSelected[0], numVectorSelected[1], OperationType);
    }
    
    // multiplicacion componente por componente y suma final
    xResult = vector1.X * vector2.X;
    yResult = vector1.Y * vector2.Y;
    zResult = vector1.Z * vector2.Z;

    pointProductResult = xResult + yResult + zResult;

    printf("\n[*] El resultado del producto punto es: %.4lf\n", pointProductResult);
    return;
}

void crossProduct() {
    // seleccion y confirmacion de vectores para producto cruz
    int confirm = 0;
    int *selectedElements;
    char *OperationType = "producto cruz";
    char **vectorTypes = calloc(2, sizeof(char*));
    vectorTypes[0] = "vector 1";
    vectorTypes[1] = "vector 2";

    VectorStruct vector1;
    VectorStruct vector2;
    VectorStruct resVector;

    // repeticion hasta confirmar los vectores correctos
    while (!confirm) {
        selectedElements = selectElements("vectores", 2, vectorTypes, OperationType);
        vector1 = MatrixVectorArray -> VectorArray[selectedElements[0]];
        vector2 = MatrixVectorArray -> VectorArray[selectedElements[1]];
        confirm = confirmVectors(vector1, vector2, selectedElements[0], selectedElements[1], OperationType);
    }

    // calculo del producto cruz usando determinantes por componente
    resVector.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
    resVector.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
    resVector.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;

    addExistVectorToArray(OperationType, resVector);
    return;
}

void addExistVectorToArray(char *OperationType, VectorStruct Vector) {
    // impresion del vector resultante antes de preguntar si se guarda
    printf("\n [*] Vector resultante:\n");
    showVector(Vector, -1);

    int confirm = confirmQuestion("Deseas agregar el vector resultante a la lista de vectores?");
    // almacenamiento opcional del vector resultante
    if (confirm) {
        char Component[90];
        int tempVectorArrayLenght = MatrixVectorArray -> VectorArrayLenght + 1;
        snprintf(Component, sizeof(Component), "%s", OperationType);

        VectorStruct *tempVectorArray = realloc(MatrixVectorArray -> VectorArray, sizeof(VectorStruct) * tempVectorArrayLenght);

        if (tempVectorArray == NULL) {
            showErrors(1, Component);
            free(tempVectorArray);
            return;
        }

        MatrixVectorArray -> VectorArray = tempVectorArray;
        MatrixVectorArray -> VectorArray[tempVectorArrayLenght - 1] = Vector;
        MatrixVectorArray -> VectorArrayLenght = tempVectorArrayLenght;

        printf("\n [*] Vector almacenado correctamente en la posicion #%d\n", tempVectorArrayLenght);
    }
}

int *selectElements(char *variableType, int numElements, char **variables, char *OperationType) {
    
    // arreglo temporal para guardar los indices seleccionados
    int *elementsSelected = calloc(numElements, sizeof(*elementsSelected));
    // limite maximo segun se seleccionen vectores o matrices
    int maxElements = (strcmp("vectores", variableType) == 0) ? MatrixVectorArray -> VectorArrayLenght : MatrixVectorArray -> MatrixArrayLenght;

    printf("\n [*] Seleccion de %s a %s\n", variableType, OperationType);

    // solicitud de cada elemento requerido para la operacion
    for (int i = 0; i < numElements; i++) {
        int confirm = 0;

        while (!confirm) {
            printf("\n [#] Ingresa el numero de %s:\n", variables[i]);
            printf(" --> ");
            scanf("%d", &elementsSelected[i]);

            if (elementsSelected[i] <= maxElements && elementsSelected[i] > 0) {
                confirm = 1;
            } else {
                showErrors(5, "");
            }
        }

        elementsSelected[i] -= 1;
    }

    return elementsSelected;
}

int confirmVectors(VectorStruct Vector1, VectorStruct Vector2, int numVector1, int numVector2, char *OperationType) {
    // confirmacion visual de los dos vectores seleccionados
    int confirm;
    
    printf("\n [!] Confirma los vectores a %s:\n", OperationType);
        
    showVector(Vector1, numVector1);
    showVector(Vector2, numVector2);

    confirm = confirmQuestion("Son correctos?");
    return confirm;
}

int confirmQuestion(char *question) {
    // pregunta generica de confirmacion para reutilizar en el programa
    int option;
    while(1) {
        printf("\n [?] %s\n", question);
        printf(" 1.- Si\n");
        printf(" 2.- No\n");
        printf(" --> ");
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
    // impresion centralizada de errores segun codigo recibido
    printf("\n\n");
    switch(ErrorCode) {
        case 1:
            printf(" [!] Error 1 (memoryError): Reserva de memoria en %s fallida.", Component);
            break;
        case 2:
            printf(" [!] Error 2 (lessThan0Value): Valor menor o igual a 0 ingresado en %s.", Component);
            break;
        case 3:
            printf(" [!] Error 3 (emptyArray): No hay %s para operar.", Component);
            break;
        case 4:
            printf(" [!] Error 4 (nullVector): El %s ingresado es nulo.", Component);
            break;
        case 5:
            printf(" [!] Error 5 (wrongValue): El valor ingresado es incorrecto.");
            break;
        case 6: 
            printf(" [!] Error 6 (notSquareMatrix): No hay coincidencia entre el numero de filas y columnas de ambas matrices.");
            break;
        case 7: 
            printf(" [!] Error 7 (notBinarialMatrix): La matriz ingresada no es binaria.");
            break;
        default: 
            printf(" [!] Error desconocido en componente %s.", Component);
    }
    printf("\n\n");
    return;
}