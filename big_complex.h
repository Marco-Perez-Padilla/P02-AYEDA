/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 1: Representación de números grandes
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 13/02/2025

** Archivo big_complex.h: Declaracion de la clase para representar numeros enteros grandes, sin limite de representacion
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      13/02/2025 - Creacion (primera version) del codigo
**/


#include <iostream>
#include "big_integer.h"

class BigComplex {
 private:
  BigInteger real_;
  BigInteger imaginary_;
 public: 
  BigComplex(const BigInteger& real, const BigInteger& imaginary = 0) : real_(real), imaginary_(imaginary) {}
  // Getters
  BigInteger getReal() const {return real_;}
  BigInteger getImaginary() const {return imaginary_;}
  // Setters 
  void setReal(const BigInteger& real) {real_ = real;}
  void setImaginary(const BigInteger& imaginary) {imaginary_ = imaginary;}
};
BigComplex operator+(const BigComplex& big_complex_1, const BigComplex& big_complex_2);
BigComplex operator-(const BigComplex& big_complex_1, const BigComplex& big_complex_2);
std::ostream& operator<<(std::ostream& os, const BigComplex& big_complex_1);