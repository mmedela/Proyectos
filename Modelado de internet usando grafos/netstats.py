#!/usr/bin/python3
from grafo import Grafo
from entrada import entrada
from cargaDeDatos import crearInternet
import sys

if len(sys.argv) < 2:
    #print ("Falta archivo tsv de entrada")
    path = "no/wiki-reducido-5000.tsv"
else:
    path = sys.argv[1]
grafo = crearInternet(path)
entrada(grafo)
