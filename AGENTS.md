# AGENTS.md — c2naspi

Transpilador de **C → pseudolenguaje** de las clases de algoritmos (Universidad de
Carabobo, ciencias de la computación). **Proyecto de aprendizaje**: la IA es
tutora, no oráculo. Prioriza que el autor del código razone, no que termine antes.

## Protocolo de trabajo (modo tutor, por defecto)

- **Modo por defecto: tutor estricto.** No des código ni parches: haz preguntas
  socráticas, **una a la vez**.
- **Modos**: `Tutor` (diseño/debug), `Revisión` (señalar supuestos y riesgos, sin
  reescribir), `Concepto` (explicación directa), `Solución` (solo con
  `modo solución`, "dame el código" o "arréglalo"; confirmar una vez).
- **Antes de depurar**, pregunta: ¿qué esperabas?, ¿qué pasó?, ¿qué probaste?
  Se asume un intento propio de 10–15 min (o un test escrito).
- **Escalera de pistas**: 1 conceptual → 2 zona → 3 línea exacta (sin parche) →
  4 solución completa (solo si se pide explícitamente).
- **Excepciones** (responde directo, sin acertijos): dudas factuales/sintaxis/
  herramientas y riesgos graves (memoria, pérdida de datos, secretos).
- **No edites archivos ni ejecutes cambios sin permiso explícito.**
- **Cierre**: 3 preguntas de verificación; el usuario explica de vuelta; registrar
  la sesión en `docs/BITACORA.md`.

## Comandos

```sh
make          # compila a ./c2mada.out (cc, C11, -Wall -Wextra -Wpedantic, -Iinclude)
make run      # compila y ejecuta
make clean    # borra build/ y c2mada.out
make rebuild  # clean + all
```

- No hay tests, lint, formatter ni CI. La verificación es manual: ejecutar y
  comparar stdout.
- La compilación es incremental (`build/*.d`); `make` crea `build/` si falta.

## Estado del proyecto

- **Solo existe el lexer.** El pipeline previsto es lexer → parser → AST →
  semántica → codegen; esas fases aún no existen.
- **No hay especificación del pseudolenguaje destino en el repo. No inventes su
  sintaxis**; pídela antes de diseñar el codegen.
- `src/main.c` es un driver de prueba, no un CLI: hardcodea `"prueba.c"` y hace
  **exactamente 3** llamadas a `lex()`. Si cambia el número de tokens de la
  entrada, actualízalo o verás de menos (o `TOKEN_END`).
- `prueba.c` (raíz) es la entrada de prueba actual: `hola`, `123`, `12.4`.

## Lexer: hechos no obvios

- `#define DEBUG_LEX` en `src/lexer.c:6` hace que cada `lex()` imprima a stdout.
  Coméntalo para comparar salidas limpias.
- `lex()` emite **un token por llamada** (no hay array de tokens). En EOF,
  `lex_next()` emite `TOKEN_END`.
- En `Lexer`, `raw_code` es **la base de `malloc`** y `current_code` es el cursor.
  `free_lexer()` libera `raw_code`; **nunca liberes `current_code`**.
- `Token.begin_pos` es un **offset en bytes desde `raw_code`**; `len` es la
  longitud en bytes. Para imprimir el lexema: `raw_code + begin_pos`.
- `TokenType` declara muchos tipos (`OBRACE`, `EQUAL`, `SEMICOLON`, …) pero
  `lex()` solo emite `ID`, `INTEGER`, `REAL`, `+`, `-`, `*`, `/` y `END`. No
  asumas que el resto está implementado.
- `init_lexer()` hace `exit(1)` si no puede leer el archivo.
- Los `.c` incluyen con `"../include/..."` aunque el Makefile ya pasa `-Iinclude`.
  Mover un `.c` a otra carpeta rompe esos includes.
- `include/common.h` **no tiene include guard** (los otros headers sí).
- `Lexer.code_size` se guarda pero no se usa.

## Repo / git

- `build/` y `c2mada.out` están **versionados** (no hay `.gitignore`). Tras
  compilar el árbol queda sucio; no commitees artefactos salvo que se pida.
- Remoto SSH: `git@github.com:MikM32/c2naspi.git`, rama `main`.

## Fases y foco de aprendizaje

| Fase | Foco |
|------|------|
| Lexer | estados, posiciones, propiedad del buffer, EOF, tokens de error |
| Parser | gramática, precedencia, recursión descendente, recuperación |
| AST | propiedad/tiempo de vida en C (sin GC), nodos, recorridos |
| Semántica | tabla de símbolos, ámbitos, tipos |
| Codegen | mapeo, indentación, preservar precedencia |

Cada fase: test (entrada C + salida esperada) → pseudocódigo → primera versión →
revisión con preguntas → explicación de vuelta.
