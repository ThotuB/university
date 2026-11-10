import qiskit as qi
from numpy import real
from qiskit.circuit import QuantumCircuit
from qiskit.quantum_info import Operator, Statevector
from qiskit_aer import AerSimulator


def print_cx():
    circuit = qi.QuantumCircuit(2, name="CNOT")
    circuit.cx(control_qubit=1, target_qubit=0)

    print("--- CX ---")
    print(circuit.draw(output="text"))
    print(real(Operator(circuit).data).astype(int))


def print_toff():
    circuit = qi.QuantumCircuit(3, name="TOFF")
    circuit.ccx(control_qubit1=1, control_qubit2=2, target_qubit=0)

    print("--- TOFF ---")
    print(circuit.draw(output="text"))
    print(real(Operator(circuit).data).astype(int))


def test_cx():
    qc = qi.QuantumCircuit(2)
    qc.h(1)
    qc.cx(1, 0)

    print("--- testing cx ---")
    print(qc.draw(output="text"))

    return qc


def simulate(qc: QuantumCircuit, shots: int):
    qc.add_register(qi.ClassicalRegister(2, "c"))
    qc.measure([0, 1], [0, 1])

    sim = AerSimulator()
    compiled = qi.transpile(qc, sim)
    results = sim.run(compiled, shots=shots).result()
    counts = results.get_counts()
    print(counts)


if __name__ == "__main__":
    print_cx()
    print_toff()
    # qc = test_cx()
    # simulate(qc, 1000)
