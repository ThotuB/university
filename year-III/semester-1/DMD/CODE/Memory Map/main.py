from constants import DATA_UNIT


class Data:
    def __init__(self, size, denom) -> None:
        self.size = size
        self.denom = denom

    @staticmethod
    def from_lines(address_lines):
        size = 2 ** (address_lines % 10)
        denom = DATA_UNIT[address_lines // 10 * 10]
        return Data(size, denom)

    def __div__(self, other: 'Data'):
        return self.size / other.size * 2 ** (DATA_UNIT[self.denom] - DATA_UNIT[other.denom])

    def __str__(self):
        return f'{self.size} {self.denom}'


class Processor:
    def __init__(self, bits, address_lines):
        self.bits = bits
        self.address_lines = address_lines
        self.memory_devices = []

        self.address_size = Data.from_lines(self.address_lines)

    def add_memory_devices(self, memory_devices):
        self.memory_devices.extend(memory_devices)
        
    def add_device(self, device):
        self.memory_devices.append(device)
        
    def solve(self):
        # step 1
        circuits = []
        # for device in self.memory_devices:
            

    def __str__(self) -> str:
        string = (f'Processor:\n'
                  f'\tBits: {self.bits}\n'
                  f'\tAddress Lines: {self.address_lines}\n'
                  f'\tAddress Size: {self.address_size}\n')
        return string


class Memory:
    def __init__(self, name: str, size: Data, circuit_size: Data, circuit_bits: int):
        self.name = name
        self.size = size
        self.circuit_size = circuit_size
        self.circuit_bits = circuit_bits
        self.memory_size = Data(circuit_size.size * (circuit_bits // 8), circuit_size.denom + 'B')

    def __str__(self) -> str:
        return f'{self.size} {self.name} - {self.circuit_size} x {self.circuit_bits} bits ({self.memory_size})'


if __name__ == '__main__':
    processor = Processor(32, 32)
    rom = Memory('ROM', Data(512, 'MB'), Data(128, 'M'), 16)
    sram = Memory('SRAM', Data(1, 'GB'), Data(128, 'M'), 32)
    dram = Memory('DRAM', Data(1, 'GB'), Data(128, 'M'), 8)
    
    processor.add_memory_devices([rom, sram, dram])

    print(processor)
    print(rom)
    print(sram)
    print(dram)
