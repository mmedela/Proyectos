# PRIMITIVAS
# crear un grafo                    g = grafo()
# agregar vertice "hola"            g.agregarVertice("hola")
# obtener vertice de clave "hola"   g.obtenerVertice("hola")
# agregar arista                    g.agregarArista("hola", "que tal")
# obtener adyacentes a v            v.adyacentes()
# obtener vertice al azar           g.verticeAlAzar()
# obtener todos los vertices        g.obtenerVertices()
# borrar vertice                    g.borrarVertice(v)
# borrar arista                     g.borrarArista(v,w)

# ejemplos
# ver si existe vertice "hola"  if "hola" in g
# recorrer vertices             for v in g

import random


class Vertice:
    def __init__(self, clave):
        self.id = clave
        self.conectadoA = {}

    def agregarAdyacente(self, adyacente):
        self.conectadoA[adyacente] = 1

    def borrarAdyacente(self, adyacente):
        self.conectadoA.pop(adyacente)

    def __str__(self):
        return str(self.id)

    def __hash__(self):
        return hash(self.id)

    def __eq__(self, w):
        if self.id == w.id:
            return True
        else:
            return False
  
    def adyacentes(self):
        return self.conectadoA.keys()

    def __iter__(self):
        return iter(self.conectadoA.keys())

    def obtenerId(self):
        return self.id


class Grafo:
    def __init__(self):
        self.listaVertices = {}
        self.numVertices = 0

    def agregarVertice(self, clave):
        self.numVertices += 1
        nuevoVertice = Vertice(clave)
        self.listaVertices[clave] = nuevoVertice
        return nuevoVertice

    def obtenerVertice(self, n):
        if n in self.listaVertices:
            return self.listaVertices[n]
        else:
            return None

    def __contains__(self, n):
        return n in self.listaVertices

    def agregarArista(self, de, a):
        if de not in self.listaVertices:
            return
        if a not in self.listaVertices:
            return
        if de == a:
            return
        self.listaVertices[de].agregarAdyacente(self.listaVertices[a])

    def borrarArista(self, de, a):
        if de not in self.listaVertices:
            return
        if a not in self.listaVertices:
            return
        if de == a:
            return
        self.listaVertices[de].borrarAdyacente(self.listaVertices[a])

    def borrarVertice(self, v):
        if v in self.listaVertices:
            for desde in self.listaVertices:
                self.listaVertices[desde].borrarAdyacente(self.listaVertices[v])
            self.listaVertices.pop(v)
            self.numVertices -= 1

    def obtenerVertices(self):
        return self.listaVertices.keys()

    def __iter__(self):
        return iter(self.listaVertices.values())

    def verticeAlAzar(self):
        return random.choice(list(self.listaVertices))
