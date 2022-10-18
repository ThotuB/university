import re

regex = r'[A-Z][a-zA-Z]*,[a-z]+ [0-9]+(/.)*(\.|\?)'
text = 'Hello,number 223/1/4?'

print(re.match(regex, text))