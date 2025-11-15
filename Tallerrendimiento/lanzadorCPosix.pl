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
#       - Automatización de la ejecución del programa mmClasicaPosix
#         para evaluar el rendimiento de la multiplicación de matrices
#         utilizando hilos POSIX (pthread).
#       - Ejecución del programa con diferentes tamaños de matriz y
#         distintos números de hilos.
#       - Repetición de cada combinación un número fijo de veces
#         para obtener resultados consistentes.
#       - Almacenamiento de cada ejecución en archivos .dat separados.
#       - Unificación final de todos los resultados en un archivo CSV.
#**************************************************************/

# Obtención de la ruta completa del directorio actual
$Path = `pwd`;
chomp($Path);   # Eliminación del salto de línea generado por pwd

# Nombre del programa ejecutable a evaluar
$Nombre_Ejecutable = "mmClasicaPosix";

# Arreglo con los diferentes tamaños de matriz a probar
@Size_Matriz = ("2","10","20", '500', '1000');

# Arreglo con los diferentes números de hilos a utilizar
@Num_Hilos = (1,2,4,8,16,20);

# Cantidad de repeticiones por cada configuración tamaño–hilos
$Repeticiones = 30;

# Bucle principal que recorre cada tamaño de matriz
foreach $size (@Size_Matriz){

    # Sub–bucle que recorre las configuraciones de hilos
	foreach $hilo (@Num_Hilos) {

        # Construcción del archivo donde se almacenarán los resultados
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Ciclo de repeticiones para obtener múltiples medidas
		for ($i=0; $i<$Repeticiones; $i++) {

            # Ejecución del programa y almacenamiento de la salida en el archivo .dat
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

            # Impresión en consola indicando la ejecución en curso
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}

        # Cierre estándar del archivo (aunque no se abrió mediante open)
		close($file);

        # Incremento opcional de contador (no utilizado posteriormente)
	    $p=$p+1;
	}
}

# Concatenación de todos los archivos generados en un archivo CSV global
system("cat *.dat > resultadosClasicosPosix.csv");
