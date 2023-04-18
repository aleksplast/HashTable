with open ("HamletFormated.txt", "r") as f:
    text = f.readlines()


text = str(text).split(' ')

print(text)

for i in range (len(text)):
    for j in range(16 - len(text[i])):
        text[i] += ' '

with open ("Hamlet16.txt", "w") as dest:
    for i in range(len(text)):
        dest.write(text[i])
