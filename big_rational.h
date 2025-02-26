/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 1: Representación de números grandes
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 25/02/2025

** Archivo big_rational.h: Declaracion e implementacion de la plantilla para representar numeros racionales grandes en cualquier base
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      25/02/2025 - Creacion (primera version) del codigo
**/


#ifndef BIG_RATIONAL_H
#define BIG_RATIONAL_H

#include <algorithm>
#include <sstream>

#include "big_integer.h"

template <unsigned char Base = 10> class BigRational {
 private:
  BigInteger<Base> numerator_;
  BigInteger<Base> denominator_;; // 1 if positive, 0 if negative
 public:
  // Constructors
  BigRational(const unsigned char* );
  BigRational(const BigInteger<Base>& numerator = 0, const BigInteger<Base>& denominator = 1) : numerator_(numerator), denominator_(denominator) {};
  // Getters
  const BigInteger<Base> getNumerator() const {return numerator_;}
  const BigInteger<Base> getDenominator() const {return denominator_;}
  // Setters
  void setNumerator(const BigInteger<Base>& numerator) {numerator_ = numerator;}
  void setDenominator(const BigInteger<Base>& denominator) {denominator_ = denominator;}
  // Assignation operator 
  BigRational<Base>& operator=(const BigRational<Base>&);
  // Insertion and extraction operators
  template <unsigned char B> friend std::ostream& operator<< (std::ostream&, const BigRational<Base>&);
  template <unsigned char B> friend std::istream& operator>> (std::istream&, BigRational<Base>&);
  // Comparation operators
  template <unsigned char B> friend bool operator< (const BigInteger<Base>&, const BigInteger<Base>&);
  // Arithmetic operators 
  template <unsigned char B> friend BigInteger<Base> operator+ (const BigInteger<Base>&, const BigInteger<Base>&);
  BigInteger<Base> operator-(const BigInteger<Base>&) const;
  BigInteger<Base> operator*(const BigInteger<Base>&) const;
  BigInteger<Base> operator%(const BigInteger<Base>&) const;
  template <unsigned char B> friend BigInteger<Base> operator/ (const BigInteger<Base>&, const BigInteger<Base>&);
  BigInteger<Base> mcd(const BigInteger<Base>&, const BigInteger<Base>&) const;
};


/**
 * @brief Copy constructor 
 * @param BI to be copied
 * @return BI copied
 */
template <unsigned char Base> BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& big_rational) {
  if (this != &big_rational) {
    numerator_ = big_rational.getNumerator();
    denominator_ = big_rational.getDenominator();
  }
  return *this;
}



/**
 * @brief Overload of << operator
 * @param ostream
 * @param BI number to be printed
 * @return ostream
 */
template <unsigned char Base> std::ostream& operator<<(std::ostream& os, const BigRational<Base>& num) {
  
  BigInteger<Base> numerator = num.getNumerator();
  BigInteger<Base> denominator = num.getDenominator();

  BigInteger<Base> factor = numerator.mcd(numerator, denominator);

  numerator = numerator / factor;
  denominator = denominator / factor;

  os << numerator << " / " << denominator;
   
  return os;
}



/**
 * @brief Overload of >> operator
 * @param istream
 * @param BI number to be inserted
 * @return istream
 */
template <unsigned char Base> std::istream& operator>>(std::istream& is, BigRational<Base>& num) {
  BigInteger<Base> numerator;
  BigInteger<Base> denominator;

  is >> numerator;

  char caracter;
  is >> caracter;
  if (caracter != '/') {
    std::cerr << "Error: Formato incorrecto. Debe ser 'numerador/denominador'.\n";
    exit(EXIT_FAILURE);
  }
  
  is >> denominator;

  num.setDenominator(denominator);
  num.setNumerator(numerator);
  
  if (num.getDenominator() == BigInteger<Base>(0)) {
    std::cerr << "Error: El denominador no puede ser cero.\n";
    exit(EXIT_FAILURE);
  }

  return is;
}


#endif