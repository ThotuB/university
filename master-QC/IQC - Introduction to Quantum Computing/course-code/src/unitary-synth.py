from numpy import pi
from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector


def ket_print(qc: QuantumCircuit):
    sv = Statevector(qc)
    return " + ".join(
        f"({amps:.2f})|{bits[::-1]}>" for bits, amps in sv.to_dict().items()
    )


u = QuantumCircuit(1)
u.h(0)
u.p(pi / 6, 0)
u.h(0)

print(u.draw("text"))

u = u.to_gate()
cu = u.control(1)


def print_qc(qc: QuantumCircuit):
    print(qc.draw("text"))
    print(ket_print(qc))


qc = QuantumCircuit(2)
qc.append(cu, [0, 1])

print_qc(qc)

qc2 = QuantumCircuit(2)
qc2.h(1)
qc2.cx(0, 1)
qc2.p(pi / 6, 1)
qc2.cx(0, 1)
qc2.h(1)

print_qc(qc2)
