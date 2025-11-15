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
#         mmClasicaOpenMP con diferentes tamaños de matriz y números de hilos.
#       - Generación de múltiples mediciones por cada combinación
#         tamaño–hilos para obtener resultados estables.
#       - Almacenamiento de los resultados en archivos .dat independientes.
#       - Consolidación de todos los datos en un archivo CSV final.
#**************************************************************/

# Obtención de la ruta absoluta del directorio actual
$Path = `pwd`;
chomp($Path);   # Eliminación del salto de línea de la salida del comando pwd

# Nombre del ejecutable a evaluar
$Nombre_Ejecutable = "mmClasicaOpenMP";

# Arreglo con los tamaños de matriz a utilizar en las pruebas
@Size_Matriz = ("2","10","20", '500', '1000');

# Arreglo con la cantidad de hilos a usar en la ejecución OpenMP
@Num_Hilos = (1,2,4,8,16,20);

# Número de repeticiones por cada combinación tamaño–hilos
$Repeticiones = 30;

# Ciclo principal que itera por todos los tamaños de matriz
foreach $size (@Size_Matriz){

    # Sub–bucle que itera por todas las configuraciones de hilos
	foreach $hilo (@Num_Hilos) {

        # Creación del nombre del archivo .dat donde se guardarán los resultados
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Ejecución repetida del experimento para asegurar estabilidad en los resultados
		for ($i=0; $i<$Repeticiones; $i++) {

            # Ejecución del programa con los parámetros definidos
            # y almacenando su salida en el archivo correspondiente
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

            # Impresión informativa en consola sobre la ejecución realizada
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}

        # Cierre estándar del archivo (aunque no se utilizó open explícitamente)
		close($file);

        # Contador opcional (no usado posteriormente)
	    $p=$p+1;
	}
}

# Unificación de todos los archivos generados en un único archivo CSV
system("cat *.dat > resultadosClasicosOpenMP.csv");
