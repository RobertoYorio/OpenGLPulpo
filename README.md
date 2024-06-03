# OpenGLPulpo
Este proyecto se basa en crear un maquina de feria con forma de pulpo con openGL. Para logralo he creado un cielo de estrellas con algunas que aparecen y desaparecen, creando un bonito efecto. El pulpo está hecho con triangle strip, usando GeoGebra para diseñar el contorno y obtener las coordenadas x e y. Al hacerlo con el triangle strip, pude añadir una textura al pulpo, donde cada vértice tiene un valor aleatorio de tono azul dentro de un rango.

La estrella de la práctica 4 es la "bombilla" de las farolas. El movimiento de los brazos forma una elipse. He creado unas escaleras para subir al vagón, que al comienzo de la ejecución se pliegan. Una vez plegadas, el pulpo empieza a moverse. El pulpo gira sobre sí mismo, acelerando y desacelerando.

He diseñado unos ojos cuya pupila está animada para crear un efecto "alocado". La rotación de los dedos (plataforma) está inspirada en la fórmula de la velocidad, con algunas pequeñas modificaciones. He añadido objetos que crean más ambiente, como un camino con farolas y bancos, y una barandilla alrededor del pulpo.

La cámara funciona de la siguiente manera: empieza cerca del suelo, toma altura siguiendo la trayectoria de una función sigmoide y pasa por debajo de las farolas. Una vez alcanzada cierta altura, empieza a rotar alrededor del pulpo siguiendo el patrón de un espirograma. Tras 15 segundos, hace un "zoom" hacia el pulpo, luego deshace el zoom y cambia a modo perspectiva/subjetiva (POV). Tras 10 segundos, vuelve a hacer los "zooms" y cambia otra vez a la cámara que rota alrededor del pulpo.
