︠d78b1123-85b6-46c4-9136-646f36c047c9r︠
from sage.crypto.sbox import SBox
S=SBox([14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7])
P=Permutation([1,5,8,7,3,6,2,4])
x="00001101"
x=[(x[i:i+4]) for i in range(0,8,4)]
import random
key=""
for i in range(8):
	key=key+ str(random.randint(0, 1))
print(key)
#key=[(key[i:i+4]) for i in range(0,8,4)]
res=[]
for i in x:
	c=3
	num=0
	temp1=list(i)
	for j in temp1:
		if c>0:
			num= num + int(j)*pow(2,c)
			c=c-1
	res.append(S[num])
res[0]=res[0].binary()
res[1]=res[1].binary()

result=[]
temp2=""
for i in res:
    if(len(i)<4):
        temp2=temp2+'0'+i
    else:
        temp2=temp2+i
temp3=""
for i in range(8):
    temp3=temp3+temp2[P(i+1)-1]
result=temp3
print("Before key mixing :",result)

temp4=""
for i in range(8):
    temp4=temp4+str((int(result[i])+int(key[i]))%2)
print(temp4)

print("After key mixing:",temp4)




︡0a772c02-c4b4-48d3-9fe4-c27e63dd8db7︡{"stdout":"10111010\n"}︡{"stdout":"Before key mixing : 10101110\n"}










