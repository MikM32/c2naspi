# Bitácora de aprendizaje — c2naspi

Registro del esfuerzo propio. Una entrada por sesión o por bug relevante.
El objetivo es poder **repasar** lo aprendido y detectar patrones.

## Plantilla

```
### AAAA-MM-DD — Título breve

- Contexto:
- Intento propio (qué escribí / cuánto tiempo):
- Hipótesis (qué esperaba que pasara):
- Qué pasó realmente:
- Pista recibida (nivel 1–3):
- Qué cambié:
- Qué aprendí (sin mirar la pantalla):
- Preguntas de verificación:
  1.
  2.
  3.
- Pendiente:
```

---

## Ejemplo real — bug de `lex_next`

- **Contexto**: el lexer abortaba con `free(): invalid pointer` y luego con
  violación de segmento. El puntero `current_code` avanzaba mal.
- **Intento propio**: tracé el recorrido sobre `"hola 123\n"` a mano.
- **Hipótesis**: creía que `lex_next` avanzaba un carácter por vez
  (`current_code++`).
- **Qué pasó realmente**: avanzaba `1, 2, 3, ...` acumulados
  (`current_code += current_char_pos`). Con `"hola 123\n"` terminó en `base+10`,
  fuera de la reserva de 10 bytes, y se saltó el `123`.
- **Pista recibida**: nivel 2 ("mira cómo avanzas entre caracteres").
- **Qué cambié**: `current_code++` y `current_char_pos++`; `debug_lex` pasó a
  leer desde `raw_code + begin_pos`.
- **Qué aprendí**: el cursor y el puntero base deben ser cosas distintas; `free`
  exige el puntero original de `malloc`, y un avance acumulado convierte un
  recorrido lineal en saltos que se salen del buffer.
- **Preguntas de verificación**:
  1. ¿Por qué `free(current_code)` falla si `current_code` se movió?
  2. ¿Por qué el avance acumulado puede leer fuera del buffer?
  3. ¿Qué diferencia hay entre `begin_pos` y el cursor actual?
- **Pendiente**: cubrir todos los tokens en un bucle y añadir `TOKEN_END`
  consistente.

---

## Sesiones

<!-- Añade aquí las nuevas entradas, de la más reciente a la más antigua. -->
