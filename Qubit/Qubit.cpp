#include "Qubit.h"

Qubit::Qubit(unsigned qubits) noexcept : qubitNumber(qubits) {
	generator.seed((unsigned)time(NULL));
	if (qubits != 0)
		amplitudes = Matrix(1, (unsigned)pow(2, qubits), sqrt(1.0 / pow(2, qubits)));
}

Qubit::Qubit(const Qubit& q) noexcept {
	this->qubitNumber = q.qubitNumber;
	this->amplitudes = q.amplitudes;
	this->generator = q.generator;
}

Qubit& Qubit::operator = (const Qubit& q) noexcept {
	if (this != &q) {
		this->qubitNumber = q.qubitNumber;
		this->amplitudes = q.amplitudes;
		this->generator = q.generator;
	}
	return *this;
}

Qubit::Qubit(const Qubit&& q) noexcept :
	qubitNumber(std::exchange(q.qubitNumber, 0)),
	amplitudes(std::move(q.amplitudes)),
	generator(std::move(q.generator)) {
}

Qubit& Qubit::operator = (const Qubit&& q) noexcept {
	if (this != &q) {
		std::exchange(this->qubitNumber, q.qubitNumber);
		this->amplitudes = std::move(q.amplitudes);
		this->generator = std::move(q.generator);
	}
	return *this;
}

Qubit::~Qubit() {}

std::complex<double>& Qubit::operator () (const unsigned& index) {
	return this->amplitudes(0, index);
}

const std::complex<double>& Qubit::operator () (const unsigned& index) const {
	return this->amplitudes(0, index);
}

Qubit& Qubit::operator = (const Qubit& q) {
	if (this == &q || this->amplitudes == q.amplitudes)
		return *this;
	this->amplitudes = q.amplitudes;
	this->qubitNumber = q.qubitNumber;
	return *this;
}

Qubit Qubit::operator * (const Qubit& q) {
	if (pow(2, this->qubitNumber) * pow(2, q.qubitNumber) > MAX_QUBITS) {
		std::cout << "Qubits limit exceeded\n";
		return *this;
	}
	Qubit res(this->qubitNumber + q.qubitNumber);
	for (unsigned i = 0; i < pow(2, this->qubitNumber); i++)
		for (unsigned j = 0; j < pow(2, q.qubitNumber); j++)
			res.amplitudes(0, i * q.qubitNumber + j) = this->amplitudes(0, i) * q.amplitudes(0, j);
	return res;
}

Qubit& Qubit::operator *= (const Qubit& q) {
	Qubit res = (*this) * q;
	(*this) = res;
	return *this;
}

bool Qubit::operator == (const Qubit& q) {
	return this->amplitudes == q.amplitudes;
}

bool Qubit::operator != (const Qubit& q) {
	return this->amplitudes != q.amplitudes;
}

Qubit Qubit::operator * (Matrix& m) {
	if (this->amplitudes.getCols() != m.getRows())
		return *this;
	Qubit res(this->qubitNumber);
	Matrix ampl(this->amplitudes.getRows(), m.getCols(), 0.0 + 0.0i);
	for (unsigned i = 0; i < this->amplitudes.getRows(); i++)
		for (unsigned j = 0; j < m.getCols(); j++)
			for (unsigned k = 0; k < m.getRows(); k++)
				ampl(i, j) += this->amplitudes(i, k) * m(k, j);
	res.amplitudes = ampl;
	return res;
}

Qubit& Qubit::operator *= (Matrix& m) {
	Qubit res = (*this) * m;
	(*this) = res;
	return *this;
}

bool Qubit::operator == (const Matrix& m) {
	return this->amplitudes == m;
}

bool Qubit::operator != (const Matrix& m) {
	return this->amplitudes != m;
}

void Qubit::distribute(std::vector<int> indices) {
	int count = 0;
	for (int i : indices)
		count += (int)(i > -(int)pow(2, this->qubitNumber) && i < (int)pow(2, this->qubitNumber));
	for (unsigned i = 0; i < this->amplitudes.getCols(); i++)
		this->amplitudes(0, i) = 0;
	for (int i : indices)
		if (i > -(int)pow(2, this->qubitNumber) && i < (int)pow(2, this->qubitNumber))
			this->amplitudes(0, i) = (i < 0) ? sqrt(1.0 / count) : -sqrt(1.0 / count);
	return;
}

void Qubit::concentrate(unsigned index) {
	for (unsigned i = 0; i < this->amplitudes.getMat()[0].size(); i++)
		this->amplitudes.getMat()[0][i % this->amplitudes.getMat()[0].size()] = 0 + 1 * (i == index);
	return;
}

void Qubit::reset() {
	this->amplitudes = Matrix(1, (unsigned)pow(2, this->qubitNumber), sqrt(1.0 / pow(2, this->qubitNumber)));
	return;
}

Matrix Qubit::getAmplitudes() {
	return this->amplitudes;
}

unsigned Qubit::getQubitNumber() {
	return this->qubitNumber;
}

std::vector<double> Qubit::getProbabilities() {
	std::vector<double> res;
	std::vector<std::complex<double>> ampl = (this->amplitudes).getMat()[0];
	for (std::complex<double> i : ampl)
		res.push_back(norm(i));
	return res;
}

Matrix Qubit::identity() {
	return Matrix::identity(2);
}

bool Qubit::identity(Qubit& q) {
	Matrix I = Matrix::identity((unsigned)pow(2, q.qubitNumber));
	q *= I;
	return true;
}

Matrix Qubit::pauliX() {
	Matrix X(2, 2);
	X(0, 1) = X(1, 0) = 1;
	return X;
}

bool Qubit::pauliX(Qubit& q) {
	if (q.qubitNumber != 1)
		return false;
	Matrix X = pauliX();
	q *= X;
	return true;
}

Matrix Qubit::pauliY() {
	Matrix Y(2, 2);
	Y(0, 1) = std::complex<double>(0, -1);
	Y(1, 0) = std::complex<double>(0, 1);
	return Y;
}

bool Qubit::pauliY(Qubit& q) {
	if (q.qubitNumber != 1)
		return false;
	Matrix Y = pauliY();
	q *= Y;
	return true;
}

Matrix Qubit::pauliZ() {
	Matrix Z(2, 2);
	Z(0, 0) = 1;
	Z(1, 1) = -1;
	return Z;
}

bool Qubit::pauliZ(Qubit& q) {
	if (q.qubitNumber != 1)
		return false;
	Matrix Z = pauliZ();
	q *= Z;
	return true;
}

Matrix Qubit::hadamard() {
	Matrix H(2, 2, 1);
	H(1, 1) = -1;
	H *= std::complex<double>(1 / sqrt(2), 0);
	return H;
}

bool Qubit::hadamard(Qubit& q) {
	if (q.qubitNumber != 1)
		return false;
	Matrix H = hadamard();
	q *= H;
	return true;
}

Matrix Qubit::phaseShift(double angle) {
	Matrix P(2, 2);
	P(0, 0) = 1;
	P(1, 1) = exp(std::complex<double>(0, 1) * angle);
	return P;
}

bool Qubit::phaseShift(Qubit& q, double angle) {
	if (q.qubitNumber != 1)
		return false;
	Matrix P = phaseShift(angle);
	q *= P;
	return true;
}

Matrix Qubit::swap() {
	Matrix S(4, 4);
	S(0, 0) = S(1, 2) = S(2, 1) = S(3, 3) = 1;
	return S;
}

bool Qubit::swap(Qubit& q) {
	if (q.qubitNumber != 2)
		return false;
	Matrix S = swap();
	q *= S;
	return true;
}

Matrix Qubit::rotX(double angle) {
	Matrix R(2, 2);
	R(0, 0) = R(1, 1) = cos(angle / 2);
	R(0, 1) = R(1, 0) = std::complex<double>(0, -1) * sin(angle / 2);
	return R;
}

bool Qubit::rotX(Qubit& q, double angle) {
	if (q.qubitNumber != 1)
		return false;
	Matrix R = rotX(angle);
	q *= R;
	return true;
}

Matrix Qubit::rotY(double angle) {
	Matrix R(2, 2);
	R(0, 0) = R(1, 1) = cos(angle / 2);
	R(0, 1) = -sin(angle / 2);
	R(1, 0) = sin(angle / 2);
	return R;
}

bool Qubit::rotY(Qubit& q, double angle) {
	if (q.qubitNumber != 1)
		return false;
	Matrix R = rotY(angle);
	q *= R;
	return true;
}

Matrix Qubit::rotZ(double angle) {
	Matrix R(2, 2);
	R(0, 0) = exp(std::complex<double>(0, -1) * (angle / 2));
	R(1, 1) = exp(std::complex<double>(0, 1) * (angle / 2));
	return R;
}

bool Qubit::rotZ(Qubit& q, double angle) {
	if (q.qubitNumber != 1)
		return false;
	Matrix R = rotZ(angle);
	q *= R;
	return true;
}

Matrix Qubit::controlled(unsigned qubits, std::string gate, std::string angle) {
	if (gate == "identity")
		return Matrix((unsigned)pow(2, qubits), (unsigned)pow(2, qubits), 1);
	Matrix C((unsigned)pow(2, qubits), (unsigned)pow(2, qubits));
	for (unsigned i = 0; i < (unsigned)pow(2, qubits) - 2; i++)
		C(i, i) = 1;
	Matrix lastQubit;
	if (gate == "pauliX")
		lastQubit = Qubit::pauliX();
	else if (gate == "pauliY")
		lastQubit = Qubit::pauliY();
	else if (gate == "pauliZ")
		lastQubit = Qubit::pauliZ();
	else if (gate == "hadamard")
		lastQubit = Qubit::hadamard();
	else if (gate == "swap")
		lastQubit = Qubit::swap();
	else if (gate == "phaseShift")
		lastQubit = Qubit::phaseShift(std::stod(angle));
	else if (gate == "rotX")
		lastQubit = Qubit::rotX(std::stod(angle));
	else if (gate == "rotY")
		lastQubit = Qubit::rotY(std::stod(angle));
	else if (gate == "rotZ")
		lastQubit = Qubit::rotZ(std::stod(angle));
	else
		return Matrix::identity((unsigned)pow(2, qubits));

	for (unsigned i = (unsigned)pow(2, qubits) - 1; i > (unsigned)pow(2, qubits) - 3 - 2 * (gate == "swap"); i--)
		for (unsigned j = (unsigned)pow(2, qubits) - 1; j > (unsigned)pow(2, qubits) - 3 - 2 * (gate == "swap"); j--)
			C(i, j) = lastQubit(i % lastQubit.getRows(), j % lastQubit.getCols());
	return C;
}

bool Qubit::controlled(Qubit& q, unsigned qubits, std::string gate, std::string angle) {
	if (q.qubitNumber != qubits)
		return false;
	Matrix C = controlled(qubits, gate, angle);
	q *= C;
	return true;
}

void Qubit::measure() {
	std::vector<double> prob = this->getProbabilities();
	std::discrete_distribution<int> distribution(prob.begin(), prob.end());
	std::cout << "|" << std::bitset<MAX_QUBITS>(distribution(this->generator))
		.to_string()
		.substr(MAX_QUBITS - this->qubitNumber) << ">\n";
	return;
}

void Qubit::printProbabilities() {
	std::vector<double> prob = this->getProbabilities();
	for (double i : prob)
		std::cout << i << ' ';
	std::cout << "\n";
	return;
}

std::ostream& operator << (std::ostream& out, Qubit& q) {
	if (q.qubitNumber != 0) {
		for (size_t i = 0; i < q.amplitudes.getMat()[0].size(); i++) {
			if (q.amplitudes.getMat()[0][i].imag() == 0 && q.amplitudes.getMat()[0][i].real() == 0)
				continue;
			if (i)
				printf(" + ");
			out << q.amplitudes.getMat()[0][i];
			out << "|" << std::bitset<MAX_QUBITS>(i)
				.to_string()
				.substr(MAX_QUBITS - q.qubitNumber) << ">";
		}
		out << "\n";
	}
	else
		out << "Empty qubit register\n";
	out << "\n";
	return out;
}
