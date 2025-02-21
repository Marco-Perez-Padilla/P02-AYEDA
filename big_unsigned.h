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

** Archivo big_unsigned.h: Declaracion de la clase para representar numeros naturales grandes, sin limite de representacion
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      05/02/2025 - Creacion (primera version) del codigo
**      11/02/2025 - Finalizacion del codigo
**/

#ifndef BIG_UNSIGNED_H
#define BIG_UNSIGNED_H

#include <iostream>
#include <vector>

template <unsigned char Base = 10> class BigUnsigned {
 private:
  std::vector<unsigned char> digits_;

  // Auxiliar private methods
  void Clear() {digits_.clear();}
  void ProcessZeros();
 public:
  // Constructors
  BigUnsigned(unsigned n = 0); 
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned& big_unsigned) : digits_(big_unsigned.getDigits()) {}; // Constructor de copia
  // Getters and setters
  std::vector<unsigned char> getDigits() const {return digits_;}
  void setDigits(const std::vector<unsigned char> digits) {digits_ = digits;}
  // Assignation operator 
  BigUnsigned& operator=(const BigUnsigned&);
  // Insertion and extraction operators
  friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
  friend std::istream& operator>>(std::istream&, BigUnsigned&);
  // Comparation operators
  friend bool operator<(const BigUnsigned&, const BigUnsigned&);
  // Arithmetic operators 
  friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  BigUnsigned operator%(const BigUnsigned&) const;
  friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  // Auxiliar method
  void AddDigit (unsigned char digit) {digits_.push_back(digit);} // Adds a digit
};

// Comparation operators
bool operator==(const BigUnsigned<Base>&, const BigUnsigned<Base>&);
bool operator>=(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2);
// Increment/Decrement operators
BigUnsigned<Base>& operator++(BigUnsigned<Base>&); // Pre-incremento
BigUnsigned<Base> operator++(BigUnsigned<Base>&, int); // Post-incremento
BigUnsigned<Base>& operator--(BigUnsigned<Base>&); // Pre-decremento
BigUnsigned<Base> operator--(BigUnsigned<Base>&, int); // Post-decremento


template<> class BigUnsigned<2>;

#endif