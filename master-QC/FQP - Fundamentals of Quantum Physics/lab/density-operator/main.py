import numpy as np
import quimb as qu

# Define a density matrix
rho = qu.qarray(
    [[0.5, 0.0],
    [0.0, 0.5]]
)

# Check if Hermitian
is_hermitian = np.array_equal(rho.H, rho)

# Calculate the trace and check if equal to 1
trace_rho = np.isclose(qu.trace(rho), 1)

# Calculate eigenvalues and check if non-negative
eigvals_rho = np.linalg.eigvals(rho)
eigvals_nonneg = all(eigval >= 0 for eigval in eigvals_rho)

# Condition for valid density matrix
valid_rho = (is_hermitian and trace_rho and eigvals_nonneg)

# Print results
print(f"Valid Density Matrix: {valid_rho}")

# Only proceed if valid density matrix
if valid_rho:

    # Compute rho**2
    rho_squared = rho@rho
    purity = qu.trace(rho_squared)
    if np.isclose(purity, 1):
        print("Pure State")
    else:
        print("Mixed State")
