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
#       - Automatización de la ejecución repetitiva del ejecutable
#         mmClasicaFork con distintos tamaños de matrices y números de hilos.
#       - Almacenamiento de los tiempos de ejecución en archivos .dat
#         separados por combinación tamaño–hilos.
#       - Ejecución por lotes para obtener múltiples mediciones (repeticiones).
#       - Creación de un archivo CSV final con todos los resultados consolidados.
#**************************************************************/

# Obtención de la ruta absoluta del directorio actual de trabajo
$Path = `pwd`;
chomp($Path);   # Eliminación del salto de línea agregado por el comando pwd

# Nombre del ejecutable que se desea ejecutar en cada iteración
$Nombre_Ejecutable = "mmClasicaFork";

# Arreglo con los diferentes tamaños de matriz a evaluar
@Size_Matriz = ("2","10","20", '500', '1000');

# Arreglo con los diferentes números de hilos (o procesos) a utilizar
@Num_Hilos = (1,2,4,8,16,20);

# Número total de repeticiones por cada combinación de tamaño e hilos
$Repeticiones = 30;

# Bucle principal que itera por cada tamaño de matriz
foreach $size (@Size_Matriz){

    # Sub–bucle que itera por cada cantidad de hilos
	foreach $hilo (@Num_Hilos) {

        # Construcción del nombre del archivo donde se guardarán los resultados
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Ciclo que ejecuta múltiples repeticiones del experimento
		for ($i=0; $i<$Repeticiones; $i++) {

            # Ejecución del programa con los parámetros correspondientes
            # y almacenamiento de la salida en el archivo .dat
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

            # Impresión en consola para seguimiento de la ejecución
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}

        # Cierre del archivo (aunque no se abrió explícitamente con open,
        # se mantiene por estructura tradicional del script)
		close($file);

        # Contador opcional (no utilizado posteriormente)
	    $p=$p+1;
	}
}

# Unificación de todos los archivos .dat en un único archivo CSV de resultados
system("cat *.dat > resultadosClasicosFork.csv");
