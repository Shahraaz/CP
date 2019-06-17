l = int(input())
instr = input()
innum = int(instr)
answer = innum*1000
cnt = 0
for i in range(l//2, l):
    if instr[i] == '0':
        continue
    right = int(instr[i:])
    left = int(instr[:i])
    temp = left+right
    if temp < answer:
        answer = temp
    if cnt < 4:
        cnt += 1
        continue
    break

cnt = 0
for i in range(l//2, l):
    if instr[l//2-i] == '0':
        continue
    j = l//2-i
    if j == 0:
        continue
    right = int(instr[j:])
    left = int(instr[:j])
    temp = left+right
    if temp < answer:
        answer = temp
    if cnt < 4:
        cnt += 1
        continue
    break
print(answer)
