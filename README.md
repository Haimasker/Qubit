<h1 align="center">
	Qubit
</h1>

<p align="center">
	Simple C++ implementation of qubits and it's operations.
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/haimasker/Qubit?color=blue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/haimasker/Qubit?color=blue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/haimasker/Qubit?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/haimasker/Qubit?color=blue" />
</p>

<h3 align="center">
	<a href="#preamble">Preamble</a>
	<span> · </span>
  <a href="#introduction">Introduction</a>
	<span> · </span>
  <a href="#fields">Class fields</a>
	<span> · </span>
	<a href="#constructors">Constructors and destructor</a>
	<span> · </span>
  <a href="#operators">Operators</a>
  <span> · </span>
  <a href="#gates">Quantum logic gates</a>
  <span> · </span>
  <a href="#methods">Methods</a>
</h3>

---

<a name="preamble"></a>
## Preamble

The purpose of this project is to create `Qubit` class that emulates working with qubits. <br>
Qubit quantum register is presented via [Matrix](https://github.com/Haimasker/Complex-numbers-matrix) of complex numbers.

---

<a name="introduction"></a>
## Introduction

[Qubit](https://en.wikipedia.org/wiki/Qubit) is the quantum version of classic binary bit, but it is in superposition of 0 and 1 state. <br>
Qubit register is the vector of probability amplitudes: a|0〉 + b|1〉 there `a` and `b` are complex numbers. <br>
It means that qubit can has value `0` or `1` with $|a|^2$ and $|b|^2$ probabilities respectively. <br>
$|a|^2 + |b|^2$ (sum of squared magnitudes of probability amplitudes) is equal to 1. <br>
<br>
Operations with qubit register is provided due to different [quantum logic gates](https://en.wikipedia.org/wiki/Quantum_logic_gate). <br>

---

<a name="fields"></a>
## Class fields

All of `Qubit` class fields are private <br>

1. `qubitNumber` - number of qubits in the register.
```cpp
unsigned qubitNumber;
```

2. `amplitudes` - probability amplitudes of the register.
```cpp
Matrix amplitudes;
```

3. `generator` - random generator for qubit state measuring.
```cpp
std::default_random_engine generator;
```

---

<a name="constructors"></a>
## Constructors and destructor

1. The Constructor receiving the number of qubits in the register. <br>
By default has value `0`. <br>
Probability amplitudes are uniformly distributed between the states of the qubit.
```cpp
Qubit(unsigned = 0) noexcept;
```

<br>

2. Copy constructor.
```cpp
Qubit(const Qubit&) noexcept;
```

<br>

3. Destructor.
```cpp
virtual ~Qubit();
```

---

<a name="operators"></a>
## Operators

1. Call operator for non-const objects receiving `index` of the qubit state. <br>
Indices are cycled, so there is no out-of-range error.
```cpp
std::complex<double>& operator () (const unsigned&);
```

<br>

2. Call operator for const objects receiving `index` of the qubit state. <br>
Indices are cycled, so there is no out-of-range error.
```cpp
const std::complex<double>& operator () (const unsigned&) const;
```

<br>

3. Copy assignment operator.
```cpp
Qubit& operator = (const Qubit&);
```

<br>

4. Multiplication operator. <br>
Merges qubits registers.
```cpp
Qubit operator * (const Qubit&);
```

<br>

5. Multiplication assignment operator. <br>
Merges qubits registers.
```cpp
Qubit& operator *= (const Qubit&);
```

<br>

6. Equal operator. <br>
Determines if qubits are equal.
```cpp
bool operator == (const Qubit&);
```

<br>

7. Non-equal operator. <br>
Determines if qubits are not-equal.
```cpp
bool operator != (const Qubit&);
```

<br>

8. Multiplication operator. <br>
Multiplies `this->amplitudes` by given `Matrix`.
```cpp
Qubit operator * (Matrix&);
```

<br>

9. Multiplication assignment operator. <br>
Multiplies `this->amplitudes` by given `Matrix`.
```cpp
Qubit& operator *= (Matrix&);
```

10. Equal operator. <br>
Determines if `this->amplitudes` is equal to given `Matrix`.
```cpp
bool operator == (const Matrix&);
```

<br>

11. Non-equal operator. <br>
Determines if `this->amplitudes` is not equal to given `Matrix`.
```cpp
bool operator != (const Matrix&);
```

<br>

12. Output operator. <br>
Prints qubit register to output.
```cpp
friend std::ostream& operator << (std::ostream&, Qubit&);
```

---

<a name="gates"></a>
## Quantum logic gates

1. `Identity gate`. <br>
Returns an identity matrix with the size of a qubit register.
```cpp
static Matrix identity();
```

<br>

2. `Identity gate`. <br>
Applies an identity matrix to `this->amplitudes`. <br>
Returns `true` because this is always possible.
```cpp
static bool identity(Qubit&);
```

<br>

3. `Pauli X gate`. <br>
Returns matrix representing Pauli X gate.
```cpp
static Matrix pauliX();
```

<br>

4. `Pauli X gate`. <br>
Applies Pauli X gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool pauliX(Qubit&);
```

<br>

5. `Pauli Y gate`. <br>
Returns matrix representing Pauli Y gate.
```cpp
static Matrix pauliY();
```

<br>

6. `Pauli Y gate`. <br>
Applies Pauli Y gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool pauliY(Qubit&);
```

<br>

7. `Pauli Z gate`. <br>
Returns matrix representing Pauli Z gate.
```cpp
static Matrix pauliZ();
```

<br>

8. `Pauli Z gate`. <br>
Applies Pauli Z gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool pauliZ(Qubit&);
```

<br>

9. `Hadamard gate`. <br>
Returns matrix representing Hadamard gate.
```cpp
static Matrix hadamard();
```

<br>

10. `Hadamard gate`. <br>
Applies Hadamard gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool hadamard(Qubit&);
```

<br>

11. `Phase shift gate`. <br>
Returns matrix representing phase shift gate with given `angle`.
```cpp
static Matrix phaseShift(double);
```

<br>

12. `Phase shift gate`. <br>
Applies phase shift gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool phaseShift(Qubit&, double);
```

<br>

13. `Swap gate`. <br>
Returns matrix representing swap gate.
```cpp
static Matrix swap();
```

<br>

14. `Swap gate`. <br>
Applies swap gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool swap(Qubit&);
```

<br>

15. `Rotation X gate`. <br>
Returns matrix representing rotation X gate with given `angle`.
```cpp
static Matrix rotX(double);
```

<br>

16. `Rotation X gate`. <br>
Applies rotation X gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool rotX(Qubit&, double);
```

<br>

17. `Rotation Y gate`. <br>
Returns matrix representing rotation Y gate with given `angle`.
```cpp
static Matrix rotY(double);
```

<br>

18. `Rotation Y gate`. <br>
Applies rotation Y gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool rotY(Qubit&, double);
```

<br>

19. `Rotation Z gate`. <br>
Returns matrix representing rotation Z gate with given `angle`.
```cpp
static Matrix rotZ(double);
```

<br>

20. `Rotation Z gate`. <br>
Applies rotation Z gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool rotZ(Qubit&, double);
```

<br>

21. `Controlled gate`. <br>
Returns necessary controlled gate. <br>
First parameter is the total number of qubits in controlled gate. <br>
Second parameter is the name of the controlled gate, remainig first qubits become controling. <br>
Third parameter is the string representing `angle` for the gates where it is necessary.
```cpp
static Matrix controlled(unsigned, std::string, std::string = "");
```
<br>
For example:

```cpp
controlled(3, "swap")
```

will produce CSWAP gate,

```cpp
conctrolled(3, "NOT")
```

will produce CCNOT gate,

```cpp
controlled(2, "phaseShift", "1.5")
```

will produce C-phaseShift gate with angle 1.5 .

<br>

22. `Controlled gate`. <br>
Applies given controlled gate to `this->amplitudes`. <br>
Returns `true` if this is possible, otherwise returns `false`.
```cpp
static bool controlled(Qubit&, unsigned, std::string, std::string = "");
```

---

<a name="methods"></a>
## Methods

1. `distribute`. <br>
Uniformly distributes the probability amplitudes between given states of the qubit. <br>
If given index of state is negative, then this state's probability amplitude becomes negative.
```cpp
void distribute(std::vector<int>);
```

<br>

2. `concentrate`. <br>
Sets the probability amplitude of the state under the given index to 1. <br>
Others become 0.
```cpp
void concentrate(unsigned);
```

<br>

3. `reset`. <br>
Uniformly distributes the probability amplitudes between all states of the qubit.
```cpp
void reset();
```

<br>

4. `getAmplitudes`. <br>
Returns `this->amplitudes`.
```cpp
Matrix getAmplitudes();
```

<br>

5. `getQubitNumber`. <br>
Returns `this->qubitNumber`.
```cpp
unsigned getQubitNumber();
```

<br>

6. `getProbabilities`. <br>
Returns vector of qubit states probabilities.
```cpp
std::vector<double> getProbabilities();
```

<br>

7. `measure`. <br>
Prints measured state of qubit.
```cpp
void measure();
```

<br>

8.  `printProbabilities`. <br>
Prints qubit states probabilities.
```cpp
void printProbabilities();
```

---
