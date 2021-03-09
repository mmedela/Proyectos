package modelo;

import java.util.ArrayList;

public class BloqueRepiteN implements Bloque ,ConjuntoBloques {
        private Integer n;

    public BloqueRepiteN(Integer n) {
        this.n = n;
    }

    private ArrayList<Bloque> listaBloques = new ArrayList<Bloque>();

        public void agregarBloque(Bloque bloque) {
            listaBloques.add(bloque);
        }

        public void ejecutar(Personaje persona) {
            for (int i = 1; i <= n; i++) {
                listaBloques.forEach(bloque -> bloque.ejecutar(persona));
            }
        }

        public void ejecutarInvertido(Personaje persona) {
            ejecutar(persona);
        }


        public String getNombre(){
            return "n";
        }


        public ArrayList<Bloque> getListaBloques() {
            return listaBloques;
        }
    }


