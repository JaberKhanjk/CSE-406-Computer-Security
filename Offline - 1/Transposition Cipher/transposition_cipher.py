# from dust i have come, dust i will be

import math
import itertools


def generate_columns(n, txt, lst):
    start = 0
    finish = len(txt) // n
    inc = len(txt) // n

    for i in range(n):
        lst.append(txt[start: finish])
        start = finish
        finish += inc


def try_all_possible_combination(cols, row, hints):
    arr = []
    n = len(cols)

    for i in range(n):
        arr.append(i + 1)

    perm = list(itertools.permutations(arr))

    mx = 0
    ans = "_"
    ordering = ()

    for i in range(len(perm)):
        s = ""
        for j in range(row):
            for k in range(n):
                # perm[i] - 1 th column
                s += cols[perm[i][k] - 1][j]

        cnt = 0
        s = s.lower()
        for h in hints:
            if h in s:
                cnt += 1

        if cnt > mx:
            mx = cnt
            ans = s
            ordering = perm[i]

        if cnt == len(hints):
            break

    return mx, ans, ordering


input_text = open("in.txt", "r")
out_file = open("out.txt", "w")

ciphered = input_text.readline()
hints = input_text.readline().split()

if ciphered[len(ciphered) - 1] == '\n':
    ciphered = ciphered[:len(ciphered) - 1]

for i in range(len(hints) - 1):
    hints[i] = hints[i][:len(hints[i]) - 1]

div = set()
l = len(ciphered)
sq = int(math.sqrt(l) + 1)

for i in range(1, sq):
    if l % i == 0:
        div.add(i)
        div.add(l // i)

div = sorted(div)
# print(div)

deciphered = ciphered
ordering = ()
mx = 0

for x in div:
    if x < 1 or x > 8:
        continue

    cols = []
    row = len(ciphered) // x
    generate_columns(x, ciphered, cols)
    X, Y, Z = try_all_possible_combination(cols, row, hints)

    if mx < X:
        mx = X
        deciphered = Y
        ordering = Z

if mx == 0:
    out_file.write("nothing matched")
else:
    out_file.write(str(mx) + " hints matched out of " + str(len(hints)) + "hints\n")
    out_file.write("key length : " + str(len(ordering))+"\n")
    out_file.write("ordering of key : " + str(ordering)+"\n")
    out_file.write("deciphered text :\n")
    out_file.write(str(deciphered)+"\n")

    c = len(ordering)
    r = len(deciphered) // c
    mat = [['0' for j in range(c)] for i in range(r)]

    k = 0
    for i in range(r):
        for j in range(c):
            mat[i][j] = deciphered[k]
            k += 1

    temp = ""
    for i in range(c):
        for j in range(r):
            temp += mat[j][i]

    cnt = 0
    for i in range(len(ciphered)):
        if ciphered[i] == temp[i]:
            cnt += 1
    acc = (len(ciphered) - cnt) / len(ciphered)
    out_file.write("accuracy : " + str(acc * 100) + "%")
