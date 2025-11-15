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
#       - Script encargado de automatizar la ejecución del programa
#         mmFilasOpenMP, encargado de realizar multiplicación de matrices
#         por filas utilizando paralelismo con OpenMP.
#       - Ejecución del programa con diferentes tamaños de matriz y
#         diferentes cantidades de hilos.
#       - Repetición de cada configuración para obtener tiempos estables.
#       - Almacenamiento individual de cada combinación en archivos .dat.
#       - Generación de un archivo CSV que consolida todos los resultados.
#**************************************************************/

# Obtención de la ruta absoluta del directorio actual
$Path = `pwd`;
chomp($Path);   # Eliminación del salto de línea del comando pwd

# Nombre del ejecutable que se ejecutará repetidamente
$Nombre_Ejecutable = "mmFilasOpenMP";

# Arreglo con los tamaños de matriz que se evaluarán
@Size_Matriz = ("2","10","20", '500', '1000');

# Arreglo con los diferentes números de hilos para pruebas OpenMP
@Num_Hilos = (1,2,4,8,16,20);

# Cantidad de repeticiones por cada combinación tamaño–hilos
$Repeticiones = 30;

# Bucle principal para recorrer todos los tamaños de matriz
foreach $size (@Size_Matriz){

    # Sub–bucle para recorrer cada configuración de hilos
	foreach $hilo (@Num_Hilos) {

        # Nombre del archivo .dat donde se almacenarán los resultados
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Repetición del experimento para obtener múltiples mediciones
		for ($i=0; $i<$Repeticiones; $i++) {

            # Ejecución del programa y redirección de la salida al archivo correspondiente
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

            # Impresión en consola para verificar la ejecución en tiempo real
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}

        # Cierre estándar del archivo generado
		close($file);

        # Contador auxiliar (no utilizado posteriormente)
	    $p=$p+1;
	}
}

# Concatenación de todos los archivos generados en un único archivo CSV
system("cat *.dat > resultadosFilasOpenMPHilos.csv");
