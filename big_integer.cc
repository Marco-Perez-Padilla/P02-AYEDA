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

** Archivo big_integer.cc: Implementacion de la clase para representar numeros enteros grandes, sin limite de representacion
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      05/02/2025 - Creacion (primera version) del codigo
**      12/02/2025 - Finalizacion del codigo
**/

#include "big_integer.h"


/**
 * @brief Default constructor that builds a BigInteger (aka BI) object
 * @param int to be converted
 */
BigInteger::BigInteger(int numero) {
  // If zero (base case), build 0 with sign positive
  if (numero == 0) {
    module_.AddDigit(0);
    sign_ = 1;
  } else {
    // If negative
    if (numero < 0) {
      // Get the positive number and add it to the module
      numero = numero * (-1);
      while (numero > 0) {
        unsigned char digit = static_cast<char>(numero % 10);
        module_.AddDigit(digit);
        numero /= 10;
      }
      // Set the sign to negative
      sign_ = 0;
    } else { // If positive, add it and set the sign at positive
      while (numero > 0) {
        unsigned char digit = static_cast<char>(numero % 10);
        module_.AddDigit(digit);
        numero /= 10;
      }
      sign_ = 1;
    }
  }
}


/**
 * @brief Copy constructor 
 * @param BI to be copied
 * @return BI copied
 */
BigInteger& BigInteger::operator=(const BigInteger& big_integer) {
  if (this != &big_integer) {
    module_ = big_integer.getModule();
    sign_ = big_integer.getSign();
  }
  return *this;
}


/**
 * @brief Overload of << operator
 * @param ostream
 * @param BI number to be printed
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
  if (num.getModule().getDigits().empty()) {
    os << '0';
  } else {
    if (num.getSign() == 0) { // If negative, print "-" before the number
      os << "-";
    }
    for (int i {num.getModule().getDigits().size() - 1}; i >= 0; --i) {
      int digit = num.getModule().getDigits()[i];
      os << digit;
    }
  }
  return os;
}


/**
 * @brief Overload of >> operator
 * @param istream
 * @param BI number to be inserted
 * @return istream
 */
std::istream& operator>>(std::istream& is, BigInteger& num) {
  std::string input;
  is >> input;
  // Initialize a bool to create the BI number
  bool not_negative = true;
  // If not empty and the string starts with "-"
  if (!(input.empty()) && input[0] == '-') {
    not_negative = false; //It's negative
    input.erase(0, 1); // Erase one position starting from the position zero ("-")
  }
  num = BigInteger(BigUnsigned(reinterpret_cast<const unsigned char*>(input.data())), not_negative);
  return is;
}


/**
 * @brief Overload of < operator between two BI
 * @param BI 1 to be compared
 * @param BI 2 to be compared
 * @return if BU_1 is minor than BU_2
 */
bool operator<(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
  // Case: Both negative, the one with greater module will be greater
  if (big_integer_1.getSign() == 0 && big_integer_2.getSign() == 0) {
    return !(big_integer_1.getModule() < big_integer_2.getModule());
  } else if (big_integer_1.getSign() == 1 && big_integer_2.getSign() == 1) { // Case: Both positive, return the lesser of both modules
    return big_integer_1.getModule() < big_integer_2.getModule();
  } else if (big_integer_1.getSign() == 0 && big_integer_2.getSign() == 1) { // Case: One negative, other positive: the negative is lesser
    return true;
  } else {
    return false; // Case: Viceversa
  }
}


/**
 * @brief Overload of == operator for BI class
 * @param BU number 1 
 * @param BU number 2
 * @return bool. True if number 1 and number 2 are the same. False otherwise
 */
bool operator==(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
  // If both sign and module are the same in both numbers, they're the same
  if (big_integer_1.getSign() == big_integer_2.getSign() && big_integer_1.getModule() == big_integer_2.getModule()) {
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Overload of >= operator for BI class
 * @param BI number 1 
 * @param BI number 2
 * @return bool. True if number 1 is greater or equal than number 2. False otherwise
 */
bool operator>=(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
  return !(big_integer_1 < big_integer_2) || (big_integer_1 == big_integer_2);
}


/**
 * @brief Overload of + operator, it calculates the sum between two BI
 * @param BI number 1 to be summed
 * @param BI number 2 to be summed
 * @return BI result of the sum
 */
BigInteger operator+(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
  // Case 1: Both negative. Sum is the sum of the modules, with negative sign (-5 + (-8))
  if (big_integer_1.getSign() == 0 && big_integer_2.getSign() == 0) {
    BigUnsigned sum = big_integer_1.getModule() + big_integer_2.getModule();
    BigInteger result (sum, 0);
    return result;
  } else if (big_integer_1.getSign() == 1 && big_integer_2.getSign() == 1) { // Case 2: Both positive. Sum is the sum of the modules, with positive sign (5 + 8)
    BigUnsigned sum = big_integer_1.getModule() + big_integer_2.getModule();
    BigInteger result (sum, 1);
    return result;
  } else if (big_integer_1.getSign() == 0 && big_integer_2.getSign() == 1) { // Case 3: Number 1 negative, 2 positive. 
    if (big_integer_1.getModule() >= big_integer_2.getModule()) { // Case 3.1: If 1 is greater than 2, sum is the rest of the modules in that order (number1-number2), with negative sign (-8+5)
      BigUnsigned sum = big_integer_1.getModule() - big_integer_2.getModule();
      BigInteger result (sum, 0);
      return result;
    } else {
      BigUnsigned sum = big_integer_2.getModule() - big_integer_1.getModule(); // Case 3.2: Else, sum is the rest of the modules in reversed (Number2-number1), with positive sign (-3+5)
      BigInteger result (sum, 1);
      return result;
    }
  } else { // Case 4: Number 1 positive, 2 negative. 
    if (big_integer_1.getModule() >= big_integer_2.getModule()) { // Case 4.1: If 1 is greater than 2, sum is the rest of the modules in that order (number1-number2), with positive sign (8-5)
      BigUnsigned sum = big_integer_1.getModule() - big_integer_2.getModule();
      BigInteger result (sum, 1);
      return result;
    } else {
      BigUnsigned sum = big_integer_2.getModule() - big_integer_1.getModule();// Case 4.2: Else, sum is the rest of the modules in reversed (Number2-number1), with negative sign (3-5)
      BigInteger result (sum, 0);
      return result;
    }
  }
}


/**
 * @brief Overload of - operator, it calculates the rest between two BI
 * @param BI number 1 to be rested
 * @param BI number 2 to be rested
 * @return BI result of the rest
 */
BigInteger BigInteger::operator-(const BigInteger& big_integer_2) const {
  // Case: Both negatives (-5 - (-8)) = (-5+8). We're on the case 3 of the sum
  if (sign_ == 0 && big_integer_2.getSign() == 0) {
    BigInteger seg_term (big_integer_2.getModule(), 1);
    BigInteger result = *this + seg_term;
    return result;
  } else if (sign_ == 1 && big_integer_2.getSign() == 1) { // Case: Both positive (5 - 8). We're actually on the case 4 of the sum
    if (module_ >= big_integer_2.getModule()) {
      BigUnsigned sum = module_ - big_integer_2.getModule();
      BigInteger result (sum, 1);
      return result;
    } else {
      BigUnsigned sum = big_integer_2.getModule() - module_;
      BigInteger result (sum, 0);
      return result;
    }
  } else if (sign_ == 0 && big_integer_2.getSign() == 1) { // Case: Number 1 negative, 2 positive (-5 - 8). We're actually on the case 1 of the sum
    BigUnsigned sum = module_ + big_integer_2.getModule();
    BigInteger result (sum, 0);
    return result;
  } else { // Case: Viceversa (5 - (-8)) = (5 + 8). We're actually on the case 2 of the sum
    BigInteger seg_term (big_integer_2.getModule(), 1);
    BigInteger result = *this + seg_term;
    return result;
  }
}


/**
 * @brief Pre-increment operator. It adds 1 to a BI in pre-order
 * @param BI to be added 1
 * @return BI summed
 */
BigInteger& operator++(BigInteger& big_integer_1) {
  BigInteger unit (1);
  big_integer_1 = big_integer_1 + unit;
  return big_integer_1;
}


/**
 * @brief Post-increment operator. It adds 1 to a BI in post-order
 * @param BI to be added 1
 * @return BI summed
 */
BigInteger operator++(BigInteger& big_integer_1, int) {
  BigInteger post_integer = big_integer_1;
  BigInteger unit (1);
  big_integer_1 = big_integer_1 + unit;
  return post_integer;
}


/**
 * @brief Pre-decrement operator. It rests 1 to a BI in pre-order
 * @param BI to be added 1
 * @return BI rested
 */
BigInteger& operator--(BigInteger& big_integer_1) {
  BigInteger unit (1);
  big_integer_1 = big_integer_1 - unit;
  return big_integer_1;
}


/**
 * @brief Post-decrement operator. It rests 1 to a BI in post-order
 * @param BI to be added 1
 * @return BI rested
 */
BigInteger operator--(BigInteger& big_integer_1, int) {
  BigInteger post_integer = big_integer_1;
  BigInteger unit (1);
  big_integer_1 = big_integer_1 - unit;
  return post_integer;
}


/**
 * @brief Overload of % operator for BI class
 * @param BI denominator
 * @return BI module result
 */
BigInteger BigInteger::operator%(const BigInteger& big_integer) const {
  // Result is the module of the modules
  BigUnsigned mod = module_ % big_integer.getModule();
  BigInteger result (mod, 1);
  return result;
}


/**
 * @brief Overload of * operator. It returns the multiplication between two BI
 * @param BI Number 1
 * @param BI Number 2
 * @return BI result
 */
BigInteger BigInteger::operator*(const BigInteger& mult) const {
  // Result will be the multiplication of the modules. Positive if both signs are the same, negative otherwise
  BigUnsigned prod = module_ * mult.getModule();
  if ((sign_ == 0 && mult.getSign() == 0) || (sign_ == 1 && mult.getSign() == 1)) {
    BigInteger result (prod, 1);
    return result;
  } else {
    BigInteger result (prod, 0);
    return result;
  }
}


/**
 * @brief Overload of / operator. It returns the integer division between two BI
 * @param BI numerator
 * @param BI denominator
 * @return BI integer result
 */
BigInteger operator/(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
  // Result will be the multiplication of the modules. Positive if both signs are the same, negative otherwise
  BigUnsigned div = big_integer_1.getModule() / big_integer_2.getModule();
  if ((big_integer_1.getSign() == 0 && big_integer_2.getSign() == 0) || (big_integer_1.getSign() == 1 && big_integer_2.getSign() == 1)) {
    BigInteger result (div, 1);
    return result;
  } else {
    BigInteger result (div, 0);
    return result;
  }
}


/**
 * @brief GCD implementation between two BI
 * @param BI Number 1
 * @param BI Number 2
 * @return Greatest common divisor between both BI
 */
BigInteger BigInteger::mcd(const BigInteger& num_1, const BigInteger& num_2) const {
  // Getting two temporal BI to modify in the iterative version of the GCD, with motivation not to overflow the stack with recursive calls
  BigInteger temp_num_1 = num_1;
  BigInteger temp_num_2 = num_2;
  // Null Integer to compare in the while
  BigInteger null (BigUnsigned(), 1);
  // While the second number is not 0
  while (!(temp_num_2 == null)) {
    // Auxiliar number is the second number
    BigInteger temp = temp_num_2;
    // Second number is module of first and second number
    temp_num_2 = temp_num_1 % temp_num_2;
    // Getting the previous second number, that will be the first number in the first steps
    temp_num_1 = temp;
  }
  return temp_num_1;
}
