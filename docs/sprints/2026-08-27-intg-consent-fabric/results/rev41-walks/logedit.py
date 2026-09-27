import sys
p, a, b = sys.argv[1:4]
s = open(p).read(); assert s.count(a) >= 1, 'mutant pattern absent'
t = s.replace(a, b, 1); assert t != s, 'mutant no-op'; open(p, 'w').write(t); print('mutant applied')
