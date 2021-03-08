def recursion(grafo, vertice, visitados, origen, largo, camino):
    clave = vertice.obtenerId()
    visitados[clave] = 1  
    camino.append(clave)
    num_recursiones = len(camino)
    if num_recursiones > largo:
        return False
    adyacentes = vertice.adyacentes()
    if not adyacentes:
        return False
    for elemento in adyacentes:
        actual = str(elemento)
        if (actual in visitados):
            if(actual == origen):
                if num_recursiones == largo:
                    return True
        else:
            nuevo_vertice = grafo.obtenerVertice(str(elemento))                
            encontrado = recursion(grafo, nuevo_vertice, visitados, origen, largo, camino)
            if encontrado:
                return True
            camino.pop()
    return False
            
            
def buscar_dfs(grafo, clave, largo):
    visitados = {}
    vertice = grafo.obtenerVertice(clave)
    if not vertice:
        return
    camino = []
    encontrado = recursion(grafo, vertice, visitados, clave, largo, camino)
    if encontrado:
        camino.append(clave)
        return camino
    return False
    


