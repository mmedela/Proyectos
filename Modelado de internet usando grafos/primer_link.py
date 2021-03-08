from grafo import Grafo

def nav_primer_link(grafo, vertice):   
    
    w = str(vertice)
    ID = " "
    devolver = []
    devolver.append(w)
    i = 0
    v = grafo.obtenerVertice(vertice)
    if v:
        a = v.adyacentes()
        while(i != 20):
            if(a):
                c = list(a)
                ID = c[0].obtenerId()
                s = str(ID)
                if (len(s) > 0):
                    devolver.append(s)
            else:
                break
            i = i + 1
            v = grafo.obtenerVertice(ID)            
            a = v.adyacentes()          

    return devolver