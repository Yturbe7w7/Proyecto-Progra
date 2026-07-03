## 📝 Descripción del Proyecto

**PELEITAS** es un videojuego arcade de lucha en 2D desarrollado en C++ utilizando la librería SFML. El juego presenta combates rápidos e intensos entre cuatro personajes icónicos, implementando mecánicas de gravedad, colisiones precisas por hitboxes, un sistema de rondas competitivas y una Inteligencia Artificial desafiante para el modo de un solo jugador.

### 🎯 Objetivo del Juego

El objetivo principal es derrotar al oponente en un duelo a muerte al mejor de 3 rondas. Cada luchador comienza con una barra de vitalidad de **500 HP**. El jugador que logre reducir la vida de su rival a 0 o mantenga una mayor cantidad de vida cuando el temporizador de 60 segundos llegue a cero, se adjudicará la ronda. El primero en ganar 2 rondas será el campeón definitivo del combate.

### 🎮 Controles

El juego utiliza un esquema de control clásico de teclado para un manejo fluido y responsivo:

- **A / D**: Moverse hacia la izquierda y derecha.
- **W**: Saltar (solo disponible si el personaje se encuentra firmemente sobre el suelo).
- **J**: Ejecutar un Golpe Débil (ataque rápido de corto alcance).
- **K**: Ejecutar un Golpe Fuerte (ataque pesado con mayor rango).
- **U**: Ejecutar un Golpe Cargado (ataque gran alcance 100 de daño).
- **R**: Reiniciar la partida y volver al menú principal de selección (disponible una vez concluido el juego).

### ⚙️ Mecánicas

- **Física de Salto y Gravedad:** Implementación de un vector de velocidad vertical y una aceleración constante que simula de forma realista la gravedad del escenario al saltar.
- **Rotación Automática y Eje Central (Pivot):** Los personajes ajustan su escala de espejo en tiempo real para mirar siempre hacia la posición del rival. Gracias a la configuración del origen en el centro del sprite (`setOrigin`), los luchadores giran sobre su propio eje sin sufrir teletransportaciones ni desfases visuales.
- **Detección de Impactos mediante Cajas de Colisión (Hitboxes):** Los ataques generan una caja invisible temporal enfrente del personaje. Si esta intersecta (`intersects`) el cuerpo del enemigo, se calcula el daño de manera inmediata.
- **Golpes Críticos Aleatorios:** Cada golpe conectado de forma exitosa tiene un **15% de probabilidad** de convertirse en un golpe crítico, duplicando el daño infligido de 10 a 20 HP y activando un efecto visual visualmente distinto.
- **Inteligencia Artificial de Persecución:** La IA evalúa la distancia horizontal en píxeles contra el Jugador 1; si está lejos lo persigue de manera automática, y al romper la distancia de seguridad, ejecuta ráfagas de ataques combinando golpes débiles y fuertes mediante un sistema probabilístico.

### 🏆 Características

- **Selector de Personajes Interactivo:** Menú dinámico que permite elegir tanto al peleador del Jugador 1 como al rival controlado por la IA entre 4 opciones disponibles.
- **HUD e Interfaz en Tiempo Real:** Barra de vida doble (fondo de daño y barra verde de vitalidad que se encoge proporcionalmente por regla de tres), temporizador de cuenta regresiva y un marcador que muestra el estado de las rondas.
- **Variedad de Escenarios y Banda Sonora Dinámica:** Al iniciar un combate, el juego selecciona de forma aleatoria uno de los 3 fondos disponibles (`fondo0.png`, `fondo1.png`, `fondo2.png`) y reproduce de forma sincronizada y en bucle su respectiva pista de música de batalla.
- **Efectos Visuales de Impacto:** Ondas de choque circulares expansivas que aparecen en la coordenada exacta del impacto, cambiando a color rojo brillante si el ataque resulta ser un golpe crítico.

### 👥 Equipo

* **Líder**: Juan Luis Hernandez Yturbe (@Yturbe7w7)

### 🛠️ Tecnologías

- **Motor/Framework**: SFML (Simple and Fast Multimedia Library) v2.6+
- **Lenguaje**: C++ (Estándar C++17 o superior)
- **Entorno de Compilación**: GCC / G++ (MinGW para Windows) ejecutado desde PowerShell.

### 📜 Créditos

- **Diseño de Sprites**: Assets originales de personajes en formato PNG (diseños basados en los nombres clave de Rea, Subaru, Kazuma y Mio).
- **Música y Audio**: Pistas en formato `.ogg` optimizadas para reproducción continua en SFML.
- **Inspiración**: Clásicos de peleas arcade en 2D de la era de los 16-bits.