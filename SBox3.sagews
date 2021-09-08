︠e918dff3-26b1-4400-abec-240df10846e4s︠
from sage.crypto.sbox import SBox
S=SBox([7,4,0,6,2,5,1,3])
P=Permutation([2,1,3])
key1="101"
key2="010"
key3="001"
p="011"
print("Plaintext is:",p)
temp0=""
for i in range(3):
    temp0=temp0+str((int(p[i])+int(key1[i]))%2)
x=temp0
#print(x)
num=0
c=2
i=0
while(c>=0):
    t=int(x[i])
    num= num + t*pow(2,c)
    c=c-1
    i=i+1
res=S(num)
res=res.binary()
if(len(res)==2):
    res='0'+ res
elif(len(res)==1):
    res='00'+ res
#print(res)
temp=""
for i in range(3):
    temp= temp+res[P(i+1)-1]
temp1=""
for i in range(3):
    temp1=temp1+str((int(temp[i])+int(key2[i]))%2)
#print(temp1)
num=0
c=2
i=0
while(c>=0):
    t=int(temp1[i])
    num= num + t*pow(2,c)
    c=c-1
    i=i+1
res1=S(num)
res1=res1.binary()
#print(res1)
if(len(res1)==2):
    res1='0'+ res1
elif(len(res1)==1):
    res1='00'+ res1
temp2=""
for i in range(3):
    temp2=temp2+str((int(res1[i])+int(key3[i]))%2)
c=temp2
print("Ciphertext is:",c)

︡c390ac73-12f1-4b5f-a5b9-0eaa9d174805︡{"stdout":"Plaintext is: 011\n"}︡{"stdout":"Ciphertext is: 111\n"}︡{"done":true}











