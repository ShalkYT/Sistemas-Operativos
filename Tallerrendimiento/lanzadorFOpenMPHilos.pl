#!/usr/bin/perl
#**************************************************************
#                   Pontificia Universidad Javeriana
#
#     Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
#     Fecha: 14/11/2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#
#     Descripción:
#       - Automatiza la ejecución del programa mmFilasOpenMP utilizando
#         distintos tamaños de matriz y diferentes cantidades de hilos.
#       - Ejecuta múltiples repeticiones por cada configuración para
#         obtener resultados representativos y consistentes.
#       - Guarda la salida de cada ejecución en archivos .dat separados,
#         organizados por tamaño de matriz y cantidad de hilos.
#       - Consolida todos los resultados en un archivo CSV final.
#**************************************************************/

# Obtención de la ruta del directorio actual
$Path = `pwd`;
chomp($Path);   # Eliminación del salto de línea generado por pwd

# Nombre del ejecutable que será probado
$Nombre_Ejecutable = "mmFilasOpenMP";

# Tamaños de matriz a evaluar (dos tamaños específicos: 20 y 1000)
@Size_Matriz = ('20','1000');

# Cantidad de hilos a utilizar (incluye configuraciones altas como 100 y 1000)
@Num_Hilos = (1,4,20,100,1000);

# Número de repeticiones por cada par tamaño–hilos
$Repeticiones = 30;

# Ciclo principal que recorre todos los tamaños de matriz definidos
foreach $size (@Size_Matriz){

    # Ciclo interno que recorre todas las configuraciones de hilos
	foreach $hilo (@Num_Hilos) {

        # Nombre del archivo .dat donde se almacenarán los resultados
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Ejecuciones repetidas para obtener mediciones estables
		for ($i=0; $i<$Repeticiones; $i++) {

            # Ejecución del programa y almacenamiento de la salida en el archivo .dat
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

            # Impresión en consola mostrando la ejecución en curso
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}

        # Cierre estándar del archivo generado
		close($file);

        # Variable incremental opcional (no utilizada después)
	    $p=$p+1;
	}
}

# Combina todos los archivos .dat en un único archivo CSV consolidado
system("cat *.dat > resultadosFilasOpenMPHilos.csv");
