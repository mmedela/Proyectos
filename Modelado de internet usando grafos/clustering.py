def coefClustering(v):
    coef = 0
    vAdyacentes = v.adyacentes()
    k = len(vAdyacentes)
    if k < 2:
        return 0
    for w in vAdyacentes:
        for x in w.adyacentes():
            if x in vAdyacentes:
                coef += 1
    return coef/(k*(k-1))


def clustering_unitario(grafo, clave):
    v = grafo.obtenerVertice(clave)
    if not v:
        return None
    return coefClustering(v)


def clustering_total(grafo):
    coef = 0
    for v in grafo:
        coef += coefClustering(v)
    return coef/grafo.numVertices
