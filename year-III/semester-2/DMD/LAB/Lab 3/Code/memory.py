import re

data_unit = {
    'b':  1,
    'Kb': 1024,
    'Mb': 1048576,
    'Gb': 1073741824,

    'B':  8,
    'KB': 8192,
    'MB': 8388608,
    'GB': 8589934592
}

def total_memory_to_bits(memory: str) -> int:
    num = int(re.search(r'[0-9]+', memory).group())
    unit = re.search(r'[a-zA-Z]+', memory).group()

    return num * data_unit[unit]

def memory_to_bits(memory: str) -> int:
    num = int(re.search(r'[0-9]+', memory).group())
    unit = re.search(r'[a-zA-Z]+', memory).group()
    width = int(re.search(r'[0-9]+$', memory).group())

    return num * data_unit[unit] * width, width