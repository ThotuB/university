from libs.lexical_analyzer import analyze_lexically
from libs.syntactical_analyzer import analyze_syntactically
from libs.domain_analyzer import analyze_domain
import os

if __name__ == '__main__':
    for i in range(0, 1):
        file_path = os.path.dirname(os.path.abspath(__file__)) + f'\\resources\\test{i}.c'
        file_text = open(file_path, 'r').read()
        
        print(file_text)
        
        tokens = analyze_lexically(file_text)
        # for token in tokens:
        #     print(token)
        symbols = analyze_domain(tokens)
        for symbol in symbols:
            print(symbol)