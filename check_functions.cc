/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 1: Representación de números grandes
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 05/02/2025

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      05/02/2025 - Creacion (primera version) del codigo
**      12/02/2025 - Finalizacion del codigo
**/

#include <iostream>
#include "check_functions.h"

/**
 * @brief Validates the line of commands and uses Help, Usage and CheckFileError functions
 * @param int argc  
 * @param char* argv[]
 */
void ValidateCommand(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    Help();
    exit(EXIT_SUCCESS);
  }
  if (argc != 1) {
    Usage();
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./p01_big_integers -- Manage big integer type\n"
              << "Usage:                ./p01_big_integers\n"
              << "Basic operations with big numbers (no above limit)\n"
              << "\n";
}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./p01_big_integers \n"
            << "Try './p01_big_integers --help' for further information\n";
}
