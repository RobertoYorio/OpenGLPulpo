# OpenGLPulpo
Este proyecto se basa en crear un maquina de feria con forma de pulpo con openGL. Para logralo he creado un cielo de estrellas con algunas que aparecen y desaparecen, creando un bonito efecto. El pulpo está hecho con triangle strip, usando GeoGebra para diseñar el contorno y obtener las coordenadas x e y. Al hacerlo con el triangle strip, pude añadir una textura al pulpo, donde cada vértice tiene un valor aleatorio de tono azul dentro de un rango.

La estrella de la práctica 4 es la "bombilla" de las farolas. El movimiento de los brazos forma una elipse. He creado unas escaleras para subir al vagón, que al comienzo de la ejecución se pliegan. Una vez plegadas, el pulpo empieza a moverse. El pulpo gira sobre sí mismo, acelerando y desacelerando.

He diseñado unos ojos cuya pupila está animada para crear un efecto "alocado". La rotación de los dedos (plataforma) está inspirada en la fórmula de la velocidad, con algunas pequeñas modificaciones. He añadido objetos que crean más ambiente, como un camino con farolas y bancos, y una barandilla alrededor del pulpo.

La cámara funciona de la siguiente manera: empieza cerca del suelo, toma altura siguiendo la trayectoria de una función sigmoide y pasa por debajo de las farolas. Una vez alcanzada cierta altura, empieza a rotar alrededor del pulpo siguiendo el patrón de un espirograma. Tras 15 segundos, hace un "zoom" hacia el pulpo, luego deshace el zoom y cambia a modo perspectiva/subjetiva (POV). Tras 10 segundos, vuelve a hacer los "zooms" y cambia otra vez a la cámara que rota alrededor del pulpo.

[Muestra del pulpo](https://drive.google.com/file/d/1ScCRNZzKCbJvIqHXEt4lXw_krCqycLbb/view?usp=drive_link)


-------------------------------------------------------------------------------------------------

I have created a sky of stars with some of them appearing and disappearing, creating a nice effect. The octopus is made with triangle strip, using GeoGebra to design the outline and get the x and y coordinates. By doing it with triangle strip, I was able to add a texture to the octopus, where each vertex has a random value of blue hue within a range.

The star of practice 4 is the “light bulb” of the street lamps. The movement of the arms forms an ellipse. I have created some stairs to climb the wagon, which at the beginning of the execution are folded. Once folded, the octopus begins to move. The octopus rotates on itself, accelerating and decelerating.

I have designed eyes whose pupil is animated to create a “crazy” effect. The rotation of the fingers (platform) is inspired by the speed formula, with some small modifications. I have added objects that create more atmosphere, such as a path with lampposts and benches, and a railing around the octopus.

The camera works as follows: it starts close to the ground, takes height following the trajectory of a sigmoid function and passes under the lampposts. Once it reaches a certain height, it starts rotating around the octopus following the pattern of a spirogram. After 15 seconds, it zooms in on the octopus, then unzooms and switches to perspective/subjective (POV) mode. After 10 seconds, it zooms back in and switches back to the camera rotating around the octopus.

[Octopus Display](https://drive.google.com/file/d/1ScCRNZzKCbJvIqHXEt4lXw_krCqycLbb/view?usp=drive_link)
