# Click derecho
Si pulsamos y arrastramos, se moverá la cámara en primera persona (esta funcionalidad no está disponible para el modo examinar).

# Click izquierdo
Seleccionaremos uno de los objetos, la camara se posicionará capturando la atención del seleccionado en modo examinar, es decir, que se movera al rededor del objeto sin perderlo
de vista.
Para salir de una selección podemos pulsar el vacio o la letra Q (mantendrá la posicion y orientacion pero se apuntará al 0,0,0).

# Cámara: Primera persona
Se mueve en el eje X con las flechas de dirección izq-dcha o con el ratón (siempre se apunta al 0,0,0), en el eje Y con las felchas de dirección arriba-abajo o con el ratón y en el eje Z con las teclas Z para el desplazamiento positivo o X para el negativo.

# Cámara: Examinar
A veces tiene ciertos traslados por la dificultad de ajustar los números negativos, la posicion del objeto, de la cámara, el desplazamiento, etc...

# Separación de modos y cámaras
Cada cámara es independiente de las otras (es preferible no mezclar cámaras mientras estamos en una selección) pero como el modo define el movimiento, si en el modo examinar volteamos la camara boca abajo, cuando volvamos a la primera persona, seguirá volteada.

# Rueda del ratón
La rueda del raton realiza zoom in cuando la rotamos de atras hacia alante y zoom out cuando lo hacemos al reves.

# Teclado

## Opción "R"
Resetea la camara actual a los parámetros de la cámara 0.

## Opción "A"
Modo animación, sirve para las luces, la posicional se mueve y la direccional cambia de color.

## Opción "C"
Selección de cámaras.

### Opción "0"
Selecciona la cámara 0, viene por defecto selecionada.

### Opción "1"
Selecciona la cámara 1, posicionada por atrás de los objetos.

### Opción "2"
Selecciona la cámara 2, misma configuración que la cámara 0, pero ortogonal.

## Opción "V"
Entramos al modo de selección de visualización, es decir, cómo veremos el objeto. Aquí disponemos de las siguientes opciones:

### Opción "D"
Se visualizarán los vertices de los triangulos que forman el objeto.

### Opción "L"
Se visualizará el perimetro de los triangulos que forman el objeto.

### Opción "S"
Se visualizarán los triangulos coloreados que forman el objeto.

### Opción "I"
Activa el modo de visualización con iluminación, si activamos una de las opciones de visualización anterior se desactivará este modo.

#### Opción "0"
Activa la luz 0, predefinida en OpenGL.

#### Opción "1"
Activa la luz 1 (Luz Posicional).

#### Opción "2"
Activa la luz 2 (Luz Direccional).

#### Opción "A"
Permite la variación del ángulo alfa, cuando éste está activado, beta se desactiva y viceversa.

#### Opción "B"
Permite la variación del ángulo beta.

#### Opción "<"
Decrementa el valor del ángulo que esté activado.

#### Opción ">"
Aumenta el valor del ángulo que esté activado.

### Opción "Q"
Saldremos del modo de selección de visualización.

## Opción "Q"
Terminará la ejecución del programa