#pragma once

#include <iostream>
#include <bitset>
#include <complex>
#include <numeric>
#include <random>
#include <ctime>
#include "matrix.h"

using namespace std::complex_literals;

#define MAX_QUBITS 8

class Qubit {

private:
	unsigned	qubitNumber;
	Matrix		amplitudes;
	std::default_random_engine generator;

public:
	Qubit(unsigned = 0) noexcept;
	Qubit(const Qubit&) noexcept;
	Qubit&	operator = (const Qubit&) noexcept;
	Qubit(const Qubit&&) noexcept;
	Qubit&	operator = (const Qubit&&) noexcept;

	virtual ~Qubit();

	std::complex<double>&		operator () (const unsigned&);
	const std::complex<double>&	operator () (const unsigned&) const;

	Qubit&	operator = (const Qubit&);
	Qubit	operator * (const Qubit&);
	Qubit&	operator *= (const Qubit&);

	bool operator == (const Qubit&);
	bool operator != (const Qubit&);

	Qubit	operator * (Matrix&);
	Qubit&	operator *= (Matrix&);

	bool operator == (const Matrix&);
	bool operator != (const Matrix&);

	void distribute(std::vector<int>);
	void concentrate(unsigned);
	void reset();

	Matrix				getAmplitudes();
	unsigned			getQubitNumber();
	std::vector<double>		getProbabilities();

	static Matrix	identity();
	static bool	identity(Qubit&);

	static Matrix	pauliX();
	static bool	pauliX(Qubit&);

	static Matrix	pauliY();
	static bool	pauliY(Qubit&);

	static Matrix	pauliZ();
	static bool	pauliZ(Qubit&);

	static Matrix	hadamard();
	static bool	hadamard(Qubit&);

	static Matrix	phaseShift(double);
	static bool	phaseShift(Qubit&, double);

	static Matrix	swap();
	static bool	swap(Qubit&);

	static Matrix	rotX(double);
	static bool	rotX(Qubit&, double);

	static Matrix	rotY(double);
	static bool	rotY(Qubit&, double);

	static Matrix	rotZ(double);
	static bool	rotZ(Qubit&, double);

	static Matrix	controlled(unsigned, std::string, std::string = "");
	static bool	controlled(Qubit&, unsigned, std::string, std::string = "");

	void measure();

	void printProbabilities();

	friend std::ostream& operator << (std::ostream&, Qubit&);
};
