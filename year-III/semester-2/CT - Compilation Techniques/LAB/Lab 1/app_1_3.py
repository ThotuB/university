import re

regex = r'^\[\^?([^\\]|\\.)+\]$'
tests = [
    r'[abc]',
    r'[^0-9]',
    r'[\r\n\t]',
    r'[.,!?;\-]',
    r'[\\]',
    r'[\\\]',
    r'[\]',
    r'[\a\b]',
    r'[\d\]',
]


for test in tests:
    match = re.match(regex, test)
    print(match)
