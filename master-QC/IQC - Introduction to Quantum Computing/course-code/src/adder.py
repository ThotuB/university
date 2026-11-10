from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector


def ket_print(qc: QuantumCircuit):
    sv = Statevector(qc)
    return " + ".join(f"|{bits[::-1]}>" for bits, _ in sv.to_dict().items())


qc = QuantumCircuit(4)
qc.x(2)

print("in: ", ket_print(qc))

qc.h(0)
qc.h(1)

print("layer 1: ", ket_print(qc))

qc.ccx(0, 1, 3)

print("layer 2: ", ket_print(qc))

qc.cx(0, 2)

print("layer 3: ", ket_print(qc))

qc.ccx(1, 2, 3)

print("layer 4: ", ket_print(qc))

qc.cx(1, 2)

print("out: ", ket_print(qc))


print(qc.draw("text"))
