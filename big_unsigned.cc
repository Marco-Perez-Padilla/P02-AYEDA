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
**      13/20/2025 - Arreglo de la resta
**/

#include "big_unsigned.h"

const unsigned char Base {10};
/**
 * @brief Default constructor that builds a BigUnsigned object
 * @param unsigned_int number to be converted
 */
BigUnsigned<Base>::BigUnsigned(unsigned numero) {
  // Base case and default behaviour
  if (numero == 0) {
    digits_.push_back(0);
  } else {
    while (numero > 0) {
      // Getting the digit and converting it to char type
      unsigned char digit = static_cast<char>(numero % Base);
      digits_.push_back(digit);
      // Advance to the next digit
      numero /= 10;
    }
  }
}


/**
 * @brief Constrcutor to build a BigUnsigned object
 * @param unsigned_char* array of chars to be converted
 */
BigUnsigned<Base>::BigUnsigned(const unsigned char* char_array) {
  // Temporal vector. We'll use it to revert the addition order 
  std::vector<unsigned char> temp_digits;
  unsigned i {0};
  // For each char in the array, until it reaches '<\0'
  while (char_array[i] != '\0') {
    // If it's not a number, abort
    if (char_array[i] < '0' || char_array[i] > '9') { // REVISAR
      std::cerr << "The array must not contain a non-numeric character" << std::endl;
      return;
    } else {
      // Convert the digit
      unsigned char digit = char_array[i] - '0';;
      temp_digits.push_back(digit);
      ++i;
    }
  }

  // Revert the order
  for (int j = temp_digits.size() - 1; j >= 0; j--) {
    digits_.push_back(temp_digits[j]);
  }
}


/**
 * @brief Copy constructor 
 * @param BigUnsigned to be copied
 * @return BigUnsigned copied
 */
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& big_unsigned) {
  if (this != &big_unsigned) {
    digits_ = big_unsigned.getDigits();
  }
  return *this;
}


/**
 * @brief Overload of << operator
 * @param ostream
 * @param BigUnsigned number to be printed
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& num) {
  if (num.getDigits().empty()) {
    os << '0';
  } else {
    for (int i {num.getDigits().size() - 1}; i >= 0; --i) {
      int digit = num.getDigits()[i];
      os << digit;
    } // IF para hexadecimal
  }
  return os;
}


/**
 * @brief Overload of >> operator
 * @param istream
 * @param BigUnsigned number to be inserted
 * @return istream
 */
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& num) {
  std::string input;
  is >> input;
  num = BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(input.data()));
  return is;
}


/**
 * @brief Overload of < operator for BigUnsigned class. Calculates which one between two BigUnsigneds (aka BU) is the minor one
 * @param BU number 1 
 * @param BU number 2
 * @return bool. True if number 1 is less than number 2. False otherwise
 */
bool operator<(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2) {
  // The one with minor size will be the minor one between them
  if (big_unsigned_1.getDigits().size() != big_unsigned_2.getDigits().size()) {
    return big_unsigned_1.getDigits().size() < big_unsigned_2.getDigits().size();
  } else { // If same size then
    // For each digit (from more to less important)
    for (int i = big_unsigned_1.getDigits().size() - 1; i >= 0; --i) {
      // If a digit is different, the one with minor value of digit will be the minor one
      if (big_unsigned_1.getDigits()[i] < big_unsigned_2.getDigits()[i]) {
        return true;
      } else if (big_unsigned_1.getDigits()[i] > big_unsigned_2.getDigits()[i]) {
        return false;
      }
    }
    return false;
  }
}


/**
 * @brief Overload of == operator for BigUnsigned class
 * @param BU number 1 
 * @param BU number 2
 * @return bool. True if number 1 and number 2 are the same. False otherwise
 */
bool operator==(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2) {
  if (big_unsigned_1.getDigits().size() != big_unsigned_2.getDigits().size()) {
    return false;
  } else {
    for (long unsigned int i {0}; i < big_unsigned_1.getDigits().size(); ++i) {
      if (big_unsigned_1.getDigits()[i] != big_unsigned_2.getDigits()[i]) {
        return false;
      } 
    }
    return true;
  }
}


/**
 * @brief Overload of >= operator for BigUnsigned class
 * @param BU number 1 
 * @param BU number 2
 * @return bool. True if number 1 is greater or equal than number 2. False otherwise
 */
bool operator>=(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2) {
  return !(big_unsigned_1 < big_unsigned_2) || (big_unsigned_1 == big_unsigned_2);
}


/**
 * @brief Private method that clears the leading zeros resulting from sum and rest
 */
void BigUnsigned<Base>::ProcessZeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
}


/**
 * @brief Overload of + operator, it calculates the sum between two BU
 * @param BU number 1 to be summed
 * @param BU number 2 to be summed
 * @return BU result of the sum
 */
BigUnsigned<Base> operator+(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2) {
  BigUnsigned<Base> result;
  // Clearing the BU result
  result.digits_.clear();
  // Declaring a carry to count while summing
  int carry = 0;

  // Case: The two numbers have the same size
  if (big_unsigned_1.getDigits().size() == big_unsigned_2.getDigits().size()) {
    // For each digit
    for (unsigned int i {0}; i < big_unsigned_1.getDigits().size(); ++i) {
      // Getting the carry from the previous step (0 initially)
      int partial_result = carry;
      // Summing the two digits
      partial_result += big_unsigned_1.getDigits()[i] + big_unsigned_2.getDigits()[i];
      // If the sum has two digits, we've got a carry for next steps
      if (partial_result / Base >= 1) {
        // Add the module and update the carry
        result.digits_.push_back(partial_result % Base); // Revisar QUÉ se mete en hexadecimal
        carry = partial_result / Base;
      } else { // Otherwise, there is no carry
        result.digits_.push_back(partial_result % Base); // CAMBIAR EL IF DE HECHO
        carry = 0;
      }
    }
    // If in the final step we still got a carry, add it
    if (carry) {
      result.digits_.push_back(carry);
    }
  } else if (big_unsigned_1.getDigits().size() > big_unsigned_2.getDigits().size()) { // Case: Number 1 size is greater than number 2 size
    unsigned int i {0};
    // For each digit of number 2 (the minor BU), we repeat the algorithm for same sizes
    while (i < big_unsigned_2.getDigits().size()) {
      int partial_result = carry;
      partial_result += big_unsigned_1.getDigits()[i] + big_unsigned_2.getDigits()[i];
      if (partial_result / Base >= 1) {
        result.digits_.push_back(partial_result % Base);
        carry = partial_result / Base;
      } else {
        result.digits_.push_back(partial_result % Base);
        carry = 0;
      }
      ++i;
    } // Where it was the final step before, we continue by propagating the carry through the rest of the digits of the greater numebr
    while (i < big_unsigned_1.getDigits().size()) {
      int partial_result = carry;
      partial_result += big_unsigned_1.getDigits()[i];
      if (partial_result / Base >= 1) {
        result.digits_.push_back(partial_result % Base);
        carry = partial_result / Base;
      } else {
        result.digits_.push_back(partial_result % Base);
        carry = 0;
      }
      ++i;
    }
    // If we still have a carry in the final step, add it
    if (carry) {
      result.digits_.push_back(carry);
    }
  } else { // Case: Number 2 size is greater than number 1 size. Repeat the previous algorithm
    unsigned int i {0};
    while (i < big_unsigned_1.getDigits().size()) {
      int partial_result = carry;
      partial_result += big_unsigned_1.getDigits()[i] + big_unsigned_2.getDigits()[i];
      if (partial_result / Base >= 1) {
        result.digits_.push_back(partial_result % Base);
        carry = partial_result / Base;
      } else {
        result.digits_.push_back(partial_result % Base);
        carry = 0;
      }
      ++i;
    }
    while (i < big_unsigned_2.getDigits().size()) {
      int partial_result = carry;
      partial_result += big_unsigned_2.getDigits()[i];
      if (partial_result / Base >= 1) {
        result.digits_.push_back(partial_result % Base);
        carry = partial_result / Base;
      } else {
        result.digits_.push_back(partial_result % Base);
        carry = 0;
      }
      ++i;
    }
    
    if (carry) {
      result.digits_.push_back(carry);
    }
  }

  // Eliminate possible leading zeros
  result.ProcessZeros();

  return result;
}


/**
 * @brief Pre-increment operator. It adds 1 to a BU in pre-order
 * @param BU to be added 1
 * @return BU summed
 */
BigUnsigned<Base>& operator++(BigUnsigned<Base>& big_unsigned_1) {
  BigUnsigned unit (1);
  big_unsigned_1 = big_unsigned_1 + unit;
  return big_unsigned_1;
}


/**
 * @brief Post-increment operator. It adds 1 to a BU in post-order
 * @param BU to be added 1
 * @return BU summed
 */
BigUnsigned<Base> operator++(BigUnsigned<Base>& big_unsigned_1, int) {
  BigUnsigned<Base> post_unsigned = big_unsigned_1;
  BigUnsigned unit (1);
  big_unsigned_1 = big_unsigned_1 + unit;
  return post_unsigned;
}


/**
 * @brief Overload of - operator, it calculates the rest between two BU. If the result is less than zero, it'll show zero
 * @param BU number to be rested
 * @return BU result of the rest
 */
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& big_unsigned_2) const {
  BigUnsigned<Base> result;
  // If the number to be rested is greater than the current one, return 0
  if (*this < big_unsigned_2) {
    return result;
  }
  // Clear the result
  result.Clear();
  // Initialize a "carry" (for cases like when: 18-9, the carry will count that "1" after doing "8-9")
  int carry = 0;
  // Case: Both sizes are the same
  if (digits_.size() == big_unsigned_2.getDigits().size()) {
    // For each digit
    for (unsigned int i {0}; i < big_unsigned_2.getDigits().size(); ++i) {
      // Get the carry from previous step (initially zero)
      int partial_digit = carry;
      // Sum the carry to the "inferior" digit
      partial_digit += big_unsigned_2.getDigits()[i];
      // If the "superior" limit is lesser than the "inferior" (case 8-9)
      if (digits_[i] < partial_digit) {
        // The digit to be added will be result of the following formula: 10 - ("inferior" - "superior")
        partial_digit = Base - (partial_digit - digits_[i]);
        if (partial_digit / Base >= 1) {
          result.AddDigit(partial_digit % Base);
        } else {
          result.AddDigit(partial_digit); // CAMBIAR CARRY??
        }
        // Propagate the carry
        carry = 1;
      } else { // Otherwise, rest normally without carry for the next steps
        partial_digit = digits_[i] - partial_digit; 
        result.AddDigit(partial_digit);
        carry = 0;
      }
    }
  } else if (digits_.size() > big_unsigned_2.getDigits().size()) { // Case: Current size is greater than number 2 size
    unsigned int i {0};
    // For each digit of number 2, do the previous algorithm
    while (i < big_unsigned_2.getDigits().size()) {
      int partial_digit = digits_[i] - big_unsigned_2.getDigits()[i] - carry;
      if (partial_digit < 0) {
        partial_digit += Base;
        carry = 1;                    // REVISAR AQUI
      } else {
        carry = 0;
      }
      result.AddDigit(partial_digit);
      ++i;
    }
    // For the rest of the digits
    while (i < digits_.size()) {
      int partial_digit = digits_[i] - carry; 
      if (partial_digit < 0) {
        partial_digit += Base;
        carry = 1;                   // REVISAR AQUI
      } else {
          carry = 0;
      }
      result.AddDigit(partial_digit);
      ++i;
    }
  }
  // Clean zeros
  result.ProcessZeros();
  return result;
}


/**
 * @brief Pre-decrement operator. It rests 1 to a BU in pre-order
 * @param BU to be rested 1
 * @return BU rested
 */
BigUnsigned<Base>& operator--(BigUnsigned<Base>& big_unsigned_1) {
  BigUnsigned<Base> unit (1);
  big_unsigned_1 = big_unsigned_1 - unit;
  return big_unsigned_1;
}


/**
 * @brief Post-decrement operator. It rests 1 to a BU in post-order
 * @param BU to be rested 1
 * @return BU rested
 */
BigUnsigned<Base> operator--(BigUnsigned<Base>& big_unsigned_1, int) {
  BigUnsigned<Base> post_unsigned = big_unsigned_1;
  BigUnsigned<Base> unit (1);
  big_unsigned_1 = big_unsigned_1 - unit;
  return post_unsigned;
}


/**
 * @brief Overload of * operator. It returns the multiplication between two BU
 * @param BU Number 1
 * @param BU Number 2
 * @return BU result
 */
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& mult) const {
  BigUnsigned<Base> result;
  result.Clear();

  if (mult.getDigits().empty() || digits_.empty() || (mult.getDigits()[0] == 0 && mult.getDigits().size() == 1) || (digits_[0] == 0 && digits_.size() == 1)) {
    result.AddDigit(0);
    return result;
  }

  BigUnsigned<Base> counter;
  while (counter < mult) {
    result = result + *this; // Suma el número actual al resultado
    ++counter; // Incrementa el contador
  }

  return result;
}


/**
 * @brief Overload of % operator. It returns the module resulting from the integer division between two BU
 * @param BU denominator
 * @return BU module result
 */
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& big_unsigned) const {
  BigUnsigned<Base> temp_num;
  temp_num = *this;
  while (temp_num >= big_unsigned) {
    temp_num = temp_num - big_unsigned;
    temp_num.ProcessZeros();
  }

  return temp_num;
}


/**
 * @brief Overload of / operator. It returns the integer division between two BU
 * @param BU numerator
 * @param BU denominator
 * @return BU integer result
 */
BigUnsigned<Base> operator/(const BigUnsigned<Base>& big_unsigned_1, const BigUnsigned<Base>& big_unsigned_2) {
  BigUnsigned<Base> temp_num;

  if ((big_unsigned_2.getDigits().size() == 1 && big_unsigned_2.getDigits()[0] == 0) || (big_unsigned_1.getDigits().size() == 1 && big_unsigned_1.getDigits()[0] == 0) || (big_unsigned_1.getDigits().empty()) || (big_unsigned_2.getDigits().empty())) {
    temp_num.AddDigit(0);
    return temp_num;
  }

  temp_num.Clear();
  BigUnsigned<Base> counter;
  temp_num = big_unsigned_1;
  
  while (temp_num >= big_unsigned_2) {
    temp_num = temp_num - big_unsigned_2;
    ++counter; 
  }

  return counter;
}
