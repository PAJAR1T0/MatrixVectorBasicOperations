def showErrors(ErrorCode, Component=""):
    if ErrorCode == 2:
        print(f"\n[!] Error 2: Valor menor o igual a 0 en {Component}.\n")
    elif ErrorCode == 6:
        print("\n[!] Error 6: La matriz no es cuadrada.\n")
    elif ErrorCode == 7:
        print("\n[!] Error 7: La matriz no es binaria.\n")
    else:
        print("\n[!] Error: Valor incorrecto.\n")


def binarialMatrixValidation(Matrix, rows, cols):

    for row in range(rows):
        for col in range(cols):
            if Matrix[row][col] != 0 and Matrix[row][col] != 1:
                showErrors(7)
                return False

    return True


def reflexiveValidation(Matrix, rows, cols):
    for row in range(rows):
        if Matrix[row][row] != 1:
            return False
    return True


def symmetricValidation(Matrix, rows, cols):
    isSymmetric = True
    isAsymmetric = True

    for row in range(rows):
        for col in range(cols):
            if Matrix[row][col] != Matrix[col][row]:
                isSymmetric = False

            if Matrix[row][col] == 1 and Matrix[col][row] == 1:
                isAsymmetric = False

    return [isSymmetric, isAsymmetric]


def transitiveValidation(Matrix, rows, cols):
    for i in range(rows):
        for j in range(cols):
            for k in range(cols):
                if Matrix[i][j] == 1 and Matrix[j][k] == 1:
                    if Matrix[i][k] != 1:
                        return False
    return True


rows = int(input("[*] Ingresa el numero de filas de la matriz:\n--> "))
if rows <= 0:
    showErrors(2, "filas")
    exit()

cols = int(input("[*] Ingresa el numero de columnas de la matriz:\n--> "))
if cols <= 0:
    showErrors(2, "columnas")
    exit()

if rows != cols:
    showErrors(6)
    exit()

Matrix = []

for row in range(rows):
    Matrix.append([])
    for col in range(cols):
        value = int(input(f"[*] Ingresa el valor de fila {row + 1}, columna {col + 1}: "))
        Matrix[row].append(value)

if not binarialMatrixValidation(Matrix, rows, cols):
    exit()

isReflexive = reflexiveValidation(Matrix, rows, cols)
symmetricRelations = symmetricValidation(Matrix, rows, cols)
isTransitive = transitiveValidation(Matrix, rows, cols)

print("\n--> Relaciones de la matriz binaria <--")

if isReflexive:
    print("[+] Reflexiva")

if symmetricRelations[0]:
    print("[+] Simetrica")

if symmetricRelations[1]:
    print("[+] Asimetrica")

if isTransitive:
    print("[+] Transitiva")

if not isReflexive and not symmetricRelations[0] and not symmetricRelations[1] and not isTransitive:
    print("[!] No hay relaciones")