Análisis del problema:
===========

###Introducción
Se debe crear un programa que se encarga de generar un **horóscopo** para un periódico, el cual debe mostrar una serie de frases para cada uno de los 12 signos zodiacales y un número de la suerte. Estas frases se deben tomar de un archivo de texto proporcionado por el usuario el cual consta originalmente de 5 secciones temáticas, Amor, Salud, Familia, Trabajo y Otros, las cuales se diferencian de las frases porque tienen dos puntos antes de la primera letra.

Ejemplo del archivo:

	:Amor
	Peligra tu relación más importante, haz algo ahora.
	Cocina algo muy especial para esa persona que amas.

	:Salud
	Necesitas dormir más.
	Evita la carne de res.

	:Otros
	Ayuda a ese amigo que tanto te necesita.
	Haz hoy una obra de caridad.

###Archivo de texto
En el ejemplo anterior se puede ver como los temas en el archivo se identifican con dos puntos al inicio de la palabra y que cada una de las frases está separada por un cambio de línea y terminan con un punto. Además una sección temática está separada de la otra por una línea en blanco. Las frases del archivo pueden contener tildes y signos de puntuación que deben leerse y mostrarse al usuario sin problemas.

Otro aspecto a tomar en cuenta es que el programa debe funcionar sin importar la cantidad de frases que tenga el archivo de texto, ya que el usuario puede modificar el archivo sobre el que se está trabajando y el programa se debe actualizar si el archivo cambia, esto quiere decir en otras palabras que si el usuario agrega o elimina temas o frases, el programa debe actualizarse y utilizar las nuevas frases o temas. El programa debe escoger aleatoriamente una frase por cada tema, o sea que para cada signo se mostrarán 6 frases en total. Una vez que se hayan escogido las frases que se mostrarán, se deberá escoger un número aleatorio entre 0 y 99 e imprimirlo al final de las frases. Si el número mostrado es menor que 10, se le anticipará un 0. Además, el programa debe identificar cuando llega al final del archivo y ya no quedan más frases por leer.

###Consistencia del programa
El horóscopo debe tener consistencia, esto quiere decir que cada signo tiene sus respectivas frases dependiendo de la fecha, pero éstas nunca van a variar para su misma fecha y mismo signo.  Por ejemplo si se pide el horóscopo para Aries de la fecha 30/08/2016 y se muestra, entre otras, la frase “Vas a ser millonario” no importa cuántas veces se invoque, o en qué fecha se haya invocado, mientras se solicite el horóscopo de Aries para la fecha 30/08/2016 siempre se mostrará “Vas a ser millonario” y las mismas frases que aparecieron la primera vez que se invocó. En este programa la hora no es importante, sino la fecha, esto quiere decir que si se solicita el horóscopo de Géminis del día X a las 11:00 am será el mismo a las 8:00 pm del mismo día X, excepto en el caso de las 12:00 am en el que ya la fecha habrá cambiado y el horóscopo mostrado debe ser distinto. Se negoció con el usuario para que en el caso en el que se modifique el archivo pueda variar la consistencia mencionada, pero se debe advertir al usuario de que esto puede pasar.

###Interacción y parámetros
En este programa, la interacción con el usuario se va a realizar por medio de la línea de comandos, si se quiere llamar al programa se tiene que escribir el nombre del ejecutable más los parámetros que se quieran agregar. Horóscopo sería el nombre del programa llamado y después de este se agregan los parámetros, separados por espacios, estos pueden variar según lo que el usuario quiera ver del horóscopo, el usuario podrá ingresar los siguientes parámetros:

- Fecha del horóscopo: esta se deberá ingresar con un formato dd/mm/aaaa y mostrará todo el horóscopo en general de la respectiva fecha (los 12 signos). Si entre los parámetros se ingresa más de una fecha con el formato mencionado, solo se tomará la primera fecha ingresada de izquierda a derecha y se mostrará el horóscopo para ese día.
- Signos zodiacales: se debe ingresar el nombre del signo con la primera letra en mayúscula y sin tildes y mostrará las frases de los respectivos signos de la fecha ingresada. Si se repite algún signo solo debe mostrar su horóscopo una vez.
- Fecha de nacimiento: debe ser ingresada en un formato dd/mm, si se ingresa con el año se tomará como si fuera una fecha de horóscopo, este parámetro se puede llamar en caso de que el usuario no sepa cuál es su signo zodiacal por lo tanto mostrará los signos zodiacales correspondientes con sus frases escogidas.
- Sin parámetros: si el usuario no ingresa ningún parámetro se mostrará el horóscopo para los 12 signos de la fecha actual.

El programa debe de ser capaz de leer cualquiera de los datos listados anteriormente, y en ciertas ocasiones de mezclas. Esto quiere decir que el usuario podrá ingresar signos y fechas mezcladas en el orden que desee.

###Errores
En caso de que haya una mala escritura, inmediatamente el programa debe detenerse e informar al usuario que hubo una mala digitación. Si fuera el caso de que hubieran varios parámetros y que algunos de esos parámetros están correctos y otros no, sólo se mostrará que hubo un error de digitación en alguno de los parámetros. De la misma manera, si se introduce una fecha que no sea válida como por ejemplo 31/09/2006, se informará al usuario que la fecha ingresada no existe. Se debe tomar en cuenta que el 29 de febrero solo existe si el año en que se solicitó el horóscopo es bisiesto.

###Ejemplos

Entrada de ejemplo:

	./horoscopo Aries 20/12/2010 Libra 29/08 29/02/2016 Virgo

Salida de ejemplo:

	Aries:
	Haz exactamente eso que hoy escucharás como prohibido en el amor.
	Respira más lento y abre menos la boca.
	Habla ya con ese familiar antes de que sea muy tarde.
	Tramita vacaciones para la próxima semana.
	Caminante no hay camino: deja de creer en horóscopos.
	Tu número de la suerte es: 05

	Virgo:
	Tu sensibilidad te está irritando en el amor, convérsalo con tu pareja.
	Evita la carne de res.
	Cancela esa deuda familiar, esto mejorará las relaciones.
	No digas todo lo que sabes, alguien está intentado superarte en el trabajo.
	Una mascota puede disipar esa sensación de soledad.
	Tu número de la suerte es: 57

	Libra:
	Tus temores te están haciendo callar lo que sientes, es necesario que busques ayuda profesional.
	Desfruta de una golosina sin abusarte.
	Reta ese familiar a un encuentro deportivo, la victoria será tuya.
	Aprovecha tus dones de liderazgo, tus colegas estarán satisfechos.
	Gasta menos de lo que gastaste ayer, la economía está difícil.
	Tu número de la suerte es: 99

Note que en la salida, los signos zodiacales se ordenan según el orden del horóscopo, por lo tanto, el orden en que el usuario escriba los signos o fechas de nacimiento, no altera el orden del horóscopo, además este se genera para la fecha 20/12/2010, y no para el 29/02/2016, (que a su vez es válida pues 2016 es bisiesto), ya que se toma la primera fecha ingresada de izquierda a derecha. Note también que como se dijo anteriormente, si un signo se repite como en este caso Virgo, (pues la fecha 29/08 corresponde al signo Virgo) solo se mostrará el horóscopo para Virgo una vez.

###Tabla de contenidos
>[TOC]