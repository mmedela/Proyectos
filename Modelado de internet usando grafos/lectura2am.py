from grafo import Grafo
import sys

def recorrer_iter (largo, clave, listados, n_operaciones, pila, grafo, apilados):
    #print(n_operaciones)
    todo_ok = True
    if n_operaciones > largo:
        return False
    #print(clave)
    if apilados.get(clave):
        pila.remove(clave)
    pila.append(clave)
    apilados[clave] = 1
    n_operaciones += 1
    vertice = grafo.obtenerVertice(clave)
    adyacentes = vertice.adyacentes()
    for elemento in adyacentes:
        k = str(elemento)
        if listados.get(k):
            todo_ok = recorrer_iter(largo, k, listados, n_operaciones, pila, grafo, apilados)
            if not todo_ok:
                return False
    return todo_ok
              

def lectura(grafo, paginas):
    pila = []
    k = ""
    apilados = {}
    listados = {}
    k = len(paginas)
    if k > 1000:
        sys.setrecursionlimit(k + 10)
    for pagina in paginas:
        listados[pagina] = 1
    i = 0 
    no_hay_ciclos = True
    while i < k and no_hay_ciclos:
        no_hay_ciclos = recorrer_iter(k, paginas[i], listados, 0, pila, grafo, apilados)
        i += 1
    if not no_hay_ciclos:
        return False
        
    devolver = []
    k = pila.pop(-1)
    devolver.append(k)
    while pila:
        k = pila.pop(-1)
        devolver.append(k)
    return devolver
    



            

    
