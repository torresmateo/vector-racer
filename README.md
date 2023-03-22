# Underground Race

Es un juego en 3D creado utilizando OpenGL y GLUT para el manejo de la pantalla y render gráfico, 
con irrKlang 1.4.0 para el audio.

El juego es parte de la cátedra "Informática 3" del segundo semestre del 2012 
de la Universidad Católica "Nuestra Señora de la Asunción" que está ubicada en Asunción, Paraguay.
Dicha Cátedra se encuentra a cargo del Ing. Sergio Aranda

## Instrucciones

Ejecutar UndergroundRace.exe (Windows) o el ejecutable UndergroundRace (OS X)

## Reglas del Juego

El jugador controla una nave, que puede mover de forma horizontal.
El objetivo del juego es sobrevivir el mayor tiempo posible.

Existen 3 obstáculos en el juego:
    - Cubo 
    - Cilindro
    - Pirámide

Al colisionar con cualquierda de los obstáculos, se pierde una vida.
Luego de una colisión, existe un periodo corto de invulnerabilidad.
Inicialmente se cuenta con 3 vidas.

Además de los obstáculos, existen items que premian al jugador:
    - Esfera Blanca: agrega una vida.
    - Esfera Azúl: reduce la velocidad en un factor de 1.1
    - Edfera Fucsia: Invulnerabilidad por 10 segundos.


## Controles

    Flecha Izquierda    - Mover la nave a la izquierda
    Flecha Derecha      - Mover la nave a la derecha
    Q                   - Entrar a Modo Debug
    -- Controles en Modo DEbug --
    W                   - Mover la cámara hacia adelante (profundidad)
    A                   - Mover la cámara lateralmente hacia la izquierda
    S                   - Mover la cámara hacia atrás (profundidad)
    D                   - Mover la cámara lateralmente hacia la derecha
    X                   - Detener/Reiniciar la velocidad
    R                   - Reset de los valores de posición y dirección de la cámara

    Mouse Click y Drag  - Modificar la dirección de la cámara

## Detalles de la implementación

El juego está implementado en C++, los detalles más importantes de la implementación son los siguientes:

- El túnel está conformado por secciones de toros, que se definen punto por punto, se cuenta con 9 secciones 
predefinidas

- Se mantienen en memoria 3 secciones en un stack, de tal manera a hacer eficiente el dibujado, 
cada sección que se agrega se randomiza entre las curvas predefinidas.

- Los obstáculos se agregan dinámicamente a cada sección al momento de agregar una curva al stack.

- La colisión utiliza el sistema Collision Box

- La nave es un modelo Exportado de 3DS Max, cargado con un Loader de archivos .obj, el parser fue
diseñado por los alumnos.

- Las transformaciones de dibujado utilizan la implementación de matemática vectorial hecha por los alumnos.


## Autores

- [Fernando Minardi](https://github.com/fernandominardi "GitHub profile") \<minardifer@gmail.com\>
- [Mateo Torres](https://github.com/torresmateo "GitHub profile") \<torresmateo@gmail.com\>
