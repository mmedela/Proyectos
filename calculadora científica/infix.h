#ifndef _INFIX_H
#define _INFIX_H

#include "strpila.h"
#include "strutil.h"

/// pos: devuelve verdadero en caso de que 'letra' se el poredador suma, resta, multiplicacion o division y false en
///      cualquier otro caso.
bool esoperador(char letra);

/// pre: 'formula' existe y contiene una ecuacion matematicamente correcta.
/// pos: en 'formula' quedo guardada una ecuacion equivalente a la original, pero escrita usando la notacion polaca inversa.
void proc(char* formula);

///pre: 'formula' existe.
///pos: los simbolos '^' fueron reubicados de forma tal que la exprecion matematica en 'formula' respete la notacion polaca
///     inversa.
void potencia(char* formula);


#endif
