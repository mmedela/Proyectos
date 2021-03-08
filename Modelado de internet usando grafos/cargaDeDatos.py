from grafo import Grafo
import csv


def crearInternet(path):
    grafo = Grafo()
    with open(path, encoding="utf8") as direccion:
        archivo = csv.reader(direccion, delimiter="\t")
        for fila in archivo:
            for i, elemento in enumerate(fila):
                if(i == 0):
                    vertice = elemento
                    grafo.agregarVertice(elemento)

    with open(path, encoding="utf8") as direccion:
        archivo = csv.reader(direccion, delimiter="\t")
        for fila in archivo:
            for i, elemento in enumerate(fila):
                if(i == 0):
                    vertice = elemento
                else:
                    grafo.agregarArista(vertice, elemento)
    return grafo
