import re
from collections import Counter
with open('the-king-james-bible.txt') as f:
    text = f.read().lower()
words = re.findall(r'\w+', text)
print(Counter(words).most_common(10))