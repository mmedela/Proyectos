from collections import deque


def caminoMinimo(grafo, origen, destino=None):
    q = deque()
    visitados = set()
    distancia = {}
    padre = {}
    distancia[origen] = 0
    padre[origen] = None
    visitados.add(origen)
    q.append(origen)
    while q:
        v = q.popleft()
        if destino and v == destino:
            return distancia, padre
        for w in v.adyacentes():
            if w not in visitados:
                padre[w] = v
                distancia[w] = distancia[v] + 1
                visitados.add(w)
                q.append(w)
    return distancia, padre


def reconstruir_camino(padre, inicio, fin):
    camino = []
    v = fin
    if not padre.get(v):
        return None
    while v != inicio:
        camino.append(v)
        v = padre[v]
    camino.append(inicio)
    return camino


def camino_mas_corto(grafo, desde, hasta):
    v = grafo.obtenerVertice(desde)
    if not v:
        return
    w = grafo.obtenerVertice(hasta)
    if not w:
        return
    padre = caminoMinimo(grafo, v, w)[1]
    recorrido = reconstruir_camino(padre, v, w)
    return recorrido
