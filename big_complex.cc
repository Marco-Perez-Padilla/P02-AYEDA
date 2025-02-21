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

** Archivo big_unsigned.cc: Implementacion de la clase para representar numeros naturales grandes, sin limite de representacion
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      05/02/2025 - Creacion (primera version) del codigo
**      11/02/2025 - Finalizacion del codigo
**/

#include "big_complex.h"

BigComplex operator+(const BigComplex& big_complex_1, const BigComplex& big_complex_2) {
  BigInteger real_part = big_complex_1.getReal() + big_complex_2.getReal();
  BigInteger imaginary_part = big_complex_1.getImaginary() + big_complex_2.getImaginary();
  BigComplex result (real_part, imaginary_part);
  return result;
}

BigComplex operator-(const BigComplex& big_complex_1, const BigComplex& big_complex_2) {
  BigInteger real_part = big_complex_1.getReal() - big_complex_2.getReal();
  BigInteger imaginary_part = big_complex_1.getImaginary() - big_complex_2.getImaginary();
  BigComplex result (real_part, imaginary_part);
  return result;
}

std::ostream& operator<<(std::ostream& os, const BigComplex& big_complex_1) {
  os << big_complex_1.getReal() << " ";
  BigInteger null (BigUnsigned(), 1);
  if (big_complex_1.getImaginary() < null) {
    os << big_complex_1.getImaginary() << " i";
  } else {
    os << "+ " << big_complex_1.getImaginary() << " i";
  }
  return os;
}