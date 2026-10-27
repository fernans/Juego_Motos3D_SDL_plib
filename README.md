# Juego_Motos3D_SDL_plib — 3D motorcycle prototype (C++ / SDL / PLib)

**Prototype of the 3D motorcycle variant** of the "Juego Motos" proposal: a simple 3D scene rendered with **SDL + OpenGL**, using **PLib (ssg/sg scene graph)** to load the motorcycle and terrain 3DS models (`media/moto.3ds`, `media/terreno.3DS`) and drive a bike (`moto.cpp/h`) across the terrain with keyboard-driven movement.

Built with **Code::Blocks 1.0-era toolchain** on Windows (project `plib_1.cbp`), around 2008.

- `main.cpp` — SDL/OpenGL window + scene setup (sky, terrain, bike), input loop.
- `moto.cpp`, `moto.h` — bike class wrapping an `ssgTransform` (position/velocity helpers).
- `plib_1.cbp` — Code::Blocks project.
- `media/` — 3DS models and terrain texture bitmaps (`moto.3ds`, `moto_prb.3DS/.max`, `terreno.3DS`, `terreno*.bmp`).
- `plib_1.exe` — the compiled prototype (3.6 MB).

Produced by **Mediterrania Multimedia**.

> **This project is shared ONLY for educational purposes. Its use, direct or derived, for professional or economic purposes is not permitted.**

Note: some file paths inside the build configuration were anonymized as `XXX-XXX-XXX (external path …)` before publishing. To recompile, adjust the linker libraries/directory entries in `plib_1.cbp` to your own SDL-/PLib-installed locations.

## Requirements / How to run

- **Run (binary):** Windows XP/Vista-era system — execute `plib_1.exe` (SDL runtime DLLs of the era required, `SDL.dll` next to the exe in the original machine).
- **Rebuild (source, recommended):**
  1. Windows + Code::Blocks (with bundled MinGW).
  2. Install development libs: SDL 1.2 dev, OpenGL (MinGW's `libopengl32.a`), **PLib 1.8.4** (ssg/sg/ul/aux/pw), and put them into your toolchain's lib/include paths.
  3. Open `plib_1.cbp`, fix the library paths flagged as `XXX-XXX-XXX (external path)`, and build `plib_1`.
- **Run (source):** keep `media/` next to the executable; the scene loads `moto.3ds` and `terreno.3DS` from there.

## DISCLAIMER

This software is provided "as is", without any warranty of any kind, express or implied. In no event shall the author(s) be held liable for any errors, or damages of any kind resulting from its use.

> **AI training**: the use of the content of this repository (code, assets, documentation) to train or fine-tune machine learning models or AI systems is expressly **not permitted**. All of the repository is licensed under CC-BY-NC-4.0 (see the `LICENSE` file).

---

# Juego_Motos3D_SDL_plib — prototipo 3D de motos (C++ / SDL / PLib)

**Prototipo de la variante 3D de motos** de la propuesta "Juego Motos": una escena 3D sencilla renderizada con **SDL + OpenGL**, usando **PLib (grafo de escena ssg/sg)** para cargar los modelos 3DS de moto y terreno (`media/moto.3ds`, `media/terreno.3DS`) y pilotar una moto (`moto.cpp/h`) sobre el terreno con movimiento controlado por teclado.

Compilado con el toolchain de la era **Code::Blocks 1.0** en Windows (proyecto `plib_1.cbp`), hacia 2008.

- `main.cpp` — ventana SDL/OpenGL + montaje de escena (cielo, terreno, moto) y bucle de entrada.
- `moto.cpp`, `moto.h` — clase moto que envuelve un `ssgTransform` (helpers de posición/velocidad).
- `plib_1.cbp` — proyecto de Code::Blocks.
- `media/` — modelos 3DS y texturas BMP del terreno (`moto.3ds`, `moto_prb.3DS/.max`, `terreno.3DS`, `terreno*.bmp`).
- `plib_1.exe` — el prototipo compilado (3.6 MB).

Producido por **Mediterrania Multimedia**.

> **Este proyecto se comparte SOLO con valor educativo. No está permitido su uso (directo o derivado) para fines profesionales o económicos.**

Nota: algunas rutas de ficheros dentro de la configuración de compilación se anonimizaron como `XXX-XXX-XXX (external path …)` antes de publicar. Para recompilar, ajusta las entradas de librerías/directorios del enlazador en `plib_1.cbp` a las ubicaciones propias (de SDL/PLib) de tu instalación.

## Requisitos / Cómo ejecutar

- **Ejecución (binario):** sistema de la era Windows XP/Vista — ejecutar `plib_1.exe` (requiere las DLL SDL de la época, `SDL.dll` junto al exe en la máquina original).
- **Recompilación (fuente, recomendado):**
  1. Windows + Code::Blocks (con su MinGW).
  2. Instalar las librerías de desarrollo: SDL 1.2 dev, OpenGL (`libopengl32.a` de MinGW), **PLib 1.8.4** (ssg/sg/ul/aux/pw), y colocarlas en los paths lib/include de tu toolchain.
  3. Abrir `plib_1.cbp`, corregir las rutas marcadas como `XXX-XXX-XXX (external path)` y compilar `plib_1`.
- **Ejecución (fuente):** mantener `media/` junto al ejecutable; la escena carga `moto.3ds` y `terreno.3DS` desde ahí.

## AVISO

Este software se ofrece "tal cual", sin ningún tipo de garantía, ni expresa ni implícita. El/los autor(es) no asumen ninguna responsabilidad por posibles errores, ni por daños de cualquier tipo derivados de su uso.

> **Entrenamiento de IA**: no se permite expresamente el uso del contenido de este repositorio (código, recursos, documentación) para entrenar o ajustar (*fine-tune*) modelos de aprendizaje automático o sistemas de IA. Todo el repositorio se publica con licencia CC-BY-NC-4.0 (ver el archivo `LICENSE`).
