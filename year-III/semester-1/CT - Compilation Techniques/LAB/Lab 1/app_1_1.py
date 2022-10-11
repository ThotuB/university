import re

# 1.1 Date Regex
regex = r'[0-3]?[0-9]/[0-3]?[0-9]/(?:[0-9]{2})?[0-9]{2}'

tests = [
    'John was born on 21/5/1990 and Mary on 7/12/92',
    '01/2/1990',
    '01/02/1990',
    '1/02/1990',
    '1/2/1990',
]

for test in tests:
    matches = re.findall(regex, test)
    for match in matches:
        print(match)