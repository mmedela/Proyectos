from camino import camino_mas_corto
from ciclo import buscar_dfs
from clustering import clustering_unitario, clustering_total
from diametro import diametro
from lectura2am import lectura
from listar_operaciones import listar_operaciones
from primer_link import nav_primer_link
from rango import todos_en_rango
import sys


def imprimirCamino(camino):
    if not camino:
        print("No se encontro recorrido")
        return
    recorrido = camino.copy()
    while len(recorrido) > 1:
        print(recorrido.pop(), "->", end=" ")
    print(recorrido.pop())
    print("Costo:", len(camino)-1)


def entrada(grafo):
    linea = " "
    recorridoMaximo = None

    while linea:
        linea_entrada = sys.stdin.readline()
        if linea_entrada == "\n" or not linea_entrada:
            break
        linea = linea_entrada.rstrip()

        parametro = ""
        comando = linea.split(" ", 1)
        if len(comando) > 1:
            parametro = comando[1].split(",")

        if comando[0] == "camino":
            if len(parametro) != 2:
                continue
            camino = camino_mas_corto(grafo, parametro[0], parametro[1])
            imprimirCamino(camino)

        if comando[0] == "ciclo":
            if len(parametro) != 2:
                continue
            camino = buscar_dfs(grafo, parametro[0], int(parametro[1]))
            if camino:
                imprimir = " -> ".join(camino)
                print(imprimir)
            else:
                print("No se encontro recorrido")

        if comando[0] == "clustering":
            if not parametro:
                clustering = clustering_total(grafo)
            else:
                clustering = clustering_unitario(grafo, parametro[0])
                if clustering == None:
                    continue
            print("{:.3f}".format(clustering))

        if comando[0] == "lectura":
            if not parametro:
                continue
            orden = lectura(grafo, parametro)

            if orden:
                imprimir = ", ".join(orden)
                print(imprimir)
            else:
                print("No existe forma de leer las paginas en orden")

        if comando[0] == "listar_operaciones":
            listar_operaciones()

        if comando[0] == "navegacion":
            if not parametro:
                continue
            imprimir = " -> ".join(nav_primer_link(grafo, parametro[0]))
            print(imprimir)

        if comando[0] == "rango":
            if len(parametro) != 2:
                continue
            rango = todos_en_rango(grafo, parametro[0], int(parametro[1]))
            print(rango)

        if comando[0] == "diametro":
            if recorridoMaximo == None:
                recorridoMaximo = diametro(grafo)
                # diametroCalculado, desde, hasta = diametro(grafo)
            imprimirCamino(recorridoMaximo)
            # else:
            #     camino_mas_corto(grafo, desde, hasta)
