from memory import *

class Processor:
    def __init__(self, bits):
        self.bits = bits
        self.devices = []


class Device:
    def __init__(self, name, total_memory: str, memory: str):
        self.name = name

        self.total_memory_str = total_memory
        self.total_memory = memory_to_bits(total_memory)

        self.memory_str = memory
        self.memory, self.memory_width = memory_to_bits(memory)

    def __str__(self):
        return f'''{self.name}
        
                '''


if __name__ == "__main__":
    eeprom = Device("EEPROM", "256KB", "64KB * 16")