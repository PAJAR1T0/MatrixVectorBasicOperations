# Operaciones con Matrices y Vectores en C

Programa desarrollado en lenguaje C para realizar operaciones matemáticas con matrices y vectores tridimensionales utilizando memoria dinámica.

## Características

### Matrices

- Agregar matrices dinámicamente
- Mostrar matrices originales
- Mostrar matrices traspuestas
- Suma de matrices
- Resta de matrices
- Multiplicación de matrices
- Multiplicación por escalar
- Identificación de relaciones binarias:
  - Reflexiva
  - Simétrica
  - Asimétrica
  - Transitiva

### Vectores

- Agregar vectores tridimensionales
- Mostrar vectores
- Suma de vectores
- Resta de vectores
- Producto punto
- Producto cruz

---

## Tecnologías utilizadas

- Lenguaje C
- Memoria dinámica (`malloc`, `calloc`, `realloc`, `free`)
- Estructuras (`struct`)
- Arreglos dinámicos
- Punteros
- Manejo modular de funciones

---

## Estructuras principales

### MatrixStruct

Estructura utilizada para almacenar matrices originales y sus traspuestas.

```c
typedef struct {
    int rows;
    int cols;
    int trasposeRows;
    int trasposeCols;
    double **content;
    double **contentTraspose;
} MatrixStruct;
```

### VectorStruct

Estructura para almacenar vectores tridimensionales.

```c
typedef struct {
    double X;
    double Y;
    double Z;
} VectorStruct;
```

### MatrixVectorStruct

Estructura principal que almacena todos los arreglos dinámicos del programa.

```c
typedef struct {
    int MatrixArrayLenght;
    int VectorArrayLenght;
    MatrixStruct **MatrixArray;
    VectorStruct *VectorArray;
} MatrixVectorStruct;
```

---

## Compilación

### Linux / macOS

```bash
gcc main.c -o programa -lm
```

### Windows con MinGW

```bash
gcc main.c -o programa.exe -lm
```

---

## Ejecución

### Linux / macOS

```bash
./programa
```

### Windows

```bash
programa.exe
```

---

## Menú principal

```text
1.- Agregar Matriz
2.- Agregar Vector
3.- Ver opciones de operaciones
4.- Mostrar matrices originales
5.- Mostrar matrices traspuestas
6.- Mostrar vectores
7.- Salir
```

---

## Operaciones implementadas

### Operaciones con matrices

#### Suma y resta de matrices

Permite sumar o restar dos matrices siempre que ambas tengan las mismas dimensiones.

#### Multiplicación de matrices

Permite multiplicar dos matrices validando que el número de columnas de la primera matriz coincida con el número de filas de la segunda.

```text
columnas de A = filas de B
```

#### Multiplicación por escalar

Multiplica cada elemento de una matriz por un número real ingresado por el usuario.

#### Relaciones binarias

El programa permite analizar matrices binarias para identificar si representan relaciones:

- Reflexivas
- Simétricas
- Asimétricas
- Transitivas

Antes de analizar la relación, el programa valida que la matriz sea cuadrada y que todos sus valores sean únicamente `0` o `1`.

---

## Operaciones con vectores

### Suma y resta de vectores

Opera dos vectores tridimensionales componente por componente.

```text
A + B = (Ax + Bx, Ay + By, Az + Bz)
```

```text
A - B = (Ax - Bx, Ay - By, Az - Bz)
```

### Producto punto

Calcula el producto punto entre dos vectores tridimensionales.

```text
A · B = AxBx + AyBy + AzBz
```

### Producto cruz

Calcula el producto cruz entre dos vectores tridimensionales.

```text
A × B = (AyBz - AzBy, AzBx - AxBz, AxBy - AyBx)
```

---

## Manejo de memoria

El programa utiliza memoria dinámica para crear, almacenar y redimensionar matrices y vectores durante la ejecución.

Funciones usadas:

- `calloc`
- `realloc`
- `free`

También incluye validaciones para evitar errores en reservas de memoria y centraliza la impresión de errores mediante la función:

```c
showErrors()
```

---

## Validaciones implementadas

El programa valida:

- Reservas de memoria fallidas
- Dimensiones inválidas
- Matrices incompatibles para operar
- Matrices no binarias
- Vectores nulos
- Selecciones incorrectas del usuario
- Arreglos vacíos

---

## Objetivo del proyecto

Este proyecto tiene como objetivo practicar conceptos fundamentales de programación en C, tales como:

- Manejo de memoria dinámica
- Uso de punteros
- Uso de estructuras
- Arreglos dinámicos
- Modularización mediante funciones
- Operaciones con matrices
- Operaciones con vectores
- Validación de errores
- Mantenimiento de código mediante comentarios