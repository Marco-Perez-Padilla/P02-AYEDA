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

** Archivo p01_big_numbers.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las clases 
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      05/02/2025 - Creacion (primera version) del codigo
**      12/02/2025 - Version final del codigo
**/

#include <iostream>

#include "big_unsigned.h"
#include "big_integer.h"
//#include "big_complex.h"

#include "check_functions.h"

int main (int argc, char* argv[]) {

  constexpr unsigned char Base = 16;

  ValidateCommand(argc, argv);

  std::cout << "Comprobaciones para Big Unsigned." << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Caso en que el numerador es mayor al denominador: " << std::endl;
  std::cout << std::endl;

  BigUnsigned<Base> prueba_unsigned_1 (10);
  BigUnsigned<Base> prueba_unsigned_2 (10);

  std::cout << "Suma: " << prueba_unsigned_1 << " + " << prueba_unsigned_2 << " = " << prueba_unsigned_1 + prueba_unsigned_2 << std::endl;
  std::cout << "Resta: " << prueba_unsigned_1 << " - " << prueba_unsigned_2 << " = " << prueba_unsigned_1 - prueba_unsigned_2 << std::endl;
  std::cout << "Multiplicación: " << prueba_unsigned_1 << " * " << prueba_unsigned_2 << " = " << prueba_unsigned_1 * prueba_unsigned_2 << std::endl;
  std::cout << "División: " << prueba_unsigned_1 << " / " << prueba_unsigned_2 << " = " << prueba_unsigned_1 / prueba_unsigned_2 << std::endl;
  std::cout << "Módulo: " << prueba_unsigned_1 << " % " << prueba_unsigned_2 << " = " << prueba_unsigned_1 % prueba_unsigned_2 << std::endl;
  std::cout << "Comparación: " << prueba_unsigned_1 << " < " << prueba_unsigned_2 << " = " << ((prueba_unsigned_1 < prueba_unsigned_2) ? "true" : "false") << std::endl;
  std::cout << "Comparación: " << prueba_unsigned_1 << " == " << prueba_unsigned_2 << " = " << ((prueba_unsigned_1 == prueba_unsigned_2) ? "true" : "false") << std::endl;

  std::cout << std::endl;
  std::cout << "Introduzca dos números para el caso en que el numerador es menor al denominador: " << std::endl;
  std::cout << std::endl;

  BigUnsigned<Base> prueba_unsigned_3;
  std::cout << "Numerador: ";      // 1513541351354120072
  std::cin >> prueba_unsigned_3;
  BigUnsigned<Base> prueba_unsigned_4;
  std::cout << "Denominador: ";    // 543417
  std::cin >> prueba_unsigned_4;

  

  std::cout << "Suma: " << prueba_unsigned_3 << " + " << prueba_unsigned_4 << " = " << prueba_unsigned_3 + prueba_unsigned_4 << std::endl;
  std::cout << "Resta: " << prueba_unsigned_3 << " - " << prueba_unsigned_4 << " = " << prueba_unsigned_3 - prueba_unsigned_4 << std::endl;
  std::cout << "Multiplicación: " << prueba_unsigned_3 << " * " << prueba_unsigned_4 << " = " << prueba_unsigned_3 * prueba_unsigned_4 << std::endl;
  std::cout << "División: " << prueba_unsigned_3 << " / " << prueba_unsigned_4 << " = " << prueba_unsigned_3 / prueba_unsigned_4 << std::endl;
  std::cout << "Módulo: " << prueba_unsigned_3 << " % " << prueba_unsigned_4 << " = " << prueba_unsigned_3 % prueba_unsigned_4 << std::endl;
  std::cout << "Comparación: " << prueba_unsigned_3 << " < " << prueba_unsigned_4 << " = " << ((prueba_unsigned_3 < prueba_unsigned_4) ? "true" : "false") << std::endl;
  std::cout << "Comparación: " << prueba_unsigned_3 << " == " << prueba_unsigned_4 << " = " << ((prueba_unsigned_3 == prueba_unsigned_4) ? "true" : "false") << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Comprobaciones para Big Integer." << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Introduzca dos números BigInteger para realizar las comprobaciones: " << std::endl;
  std::cout << "  Casos posibles: " << std::endl;
  std::cout << "    - Numerador mayor que denominador, ambos positivos" << std::endl;
  std::cout << "    - Numerador mayor que denominador, ambos negativos" << std::endl;
  std::cout << "    - Numerador mayor que denominador, uno de ellos negativo, otro positivo" << std::endl;
  std::cout << "    - Numerador menor que denominador, ambos positivos" << std::endl;
  std::cout << "    - Numerador menor que denominador, ambos negativos" << std::endl;
  std::cout << "    - Numerador mayor que denominador, uno de ellos negativo, otro positivo" << std::endl;

  std::cout << std::endl;

  BigInteger<Base> numerador;
  std::cout << "Numerador: ";
  std::cin >> numerador;
  BigInteger<Base> denominador;
  std::cout << "Denominador: ";
  std::cin >> denominador;

  std::cout << std::endl;

  std::cout << "Suma: " << numerador << " + " << denominador << " = " << numerador + denominador << std::endl;
  std::cout << "Resta: " << numerador << " - " << denominador << " = " << numerador - denominador << std::endl;
  std::cout << "Multiplicación: " << numerador << " * " << denominador << " = " << numerador * denominador << std::endl;
  std::cout << "División: " << numerador << " / " << denominador << " = " << numerador / denominador << std::endl;
  std::cout << "Módulo: " << numerador << " % " << denominador << " = " << numerador % denominador << std::endl;
  std::cout << "Comparación: " << numerador << " < " << denominador << " = " << ((numerador < denominador) ? "true" : "false") << std::endl;
  std::cout << "Comparación: " << numerador << " == " << denominador << " = " << ((numerador == denominador) ? "true" : "false") << std::endl;
  std::cout << "Máximo común divisor: " << "mcd(" << numerador << ", " << denominador << ")" << " = " << numerador.mcd(numerador, denominador) << std::endl;

  // std::cout << std::endl;
  // std::cout << std::endl;

  // // Modificacion

  // std::cout << "Comprobaciones para Big Complex." << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // const BigInteger additional_1 (123456789, 1);
  // BigInteger additional_2;
  // std::cout << "Introduzca la parte real del segundo numero (9876543210)" << std::endl;
  // std::cin >> additional_2;
  // const BigInteger additional_3 (123456788, 0);

  // BigComplex num1 (additional_1, additional_1);
  // BigComplex num2 (9876543210, additional_3);

  // std::cout << "num1: " << num1 << std::endl;
  // std::cout << "num2: " << num2 << std::endl;
  
  // std::cout << std::endl;

  // std::cout << "Suma: " << num1 + num2 << std::endl;
  return 0;
}