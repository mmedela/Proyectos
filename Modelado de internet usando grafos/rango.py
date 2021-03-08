from collections import deque


def todos_en_rango(grafo, clave, n):
    origen = grafo.obtenerVertice(clave)
    if not origen:
        return
    visitados = set()
    enRango = 0
    orden = {}
    q = deque()

    orden[origen] = 0
    visitados.add(origen)
    q.append(origen)

    while q:
        v = q.popleft()
        for w in v.adyacentes():
            if w in visitados:
                continue
            orden[w] = orden[v]+1
            if orden[w] == n:
                enRango += 1
            else:
                q.append(w)
            visitados.add(w)
    return enRango
