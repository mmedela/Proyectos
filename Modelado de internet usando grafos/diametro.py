from grafo import Grafo
from camino import caminoMinimo, camino_mas_corto


def diametro(grafo):
    diametro = 0
    for v in grafo:
        distancia = caminoMinimo(grafo, v)[0]
        verticeMasLejano = max(distancia, key=distancia.get)
        dist = distancia[verticeMasLejano]
        if dist > diametro:
            diametro = dist
            desde = v
            hasta = verticeMasLejano
    recorridoMaximo = camino_mas_corto(grafo, desde.id, hasta.id)
    return recorridoMaximo
