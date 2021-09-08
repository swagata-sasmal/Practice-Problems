def decrypt(text):
   
    n=len(text)
    Text=list(text)
    Plain_Text=''
    key={1:'EURUSHOLMES',2:'MARYWATSON',3:'IRENE',4:'SHERLOCKED',5:'REICHENBACHFALL'}
    val=list(key.values())
    for k in val:
        m=len(k)
        temp=list(k)
        key_extn=temp
        P=[]
        for i in range(n-m):
            key_extn.append(temp[i])
        for i in range(n):
            c=(ord(Text[i])-ord(key_extn[i])+26)%26
            P.append(chr(c+65))
        c=0
        for i in P:
            if(i=='A' or i=='E' or i=='I' or i=='O' or i=='U'):
                c=c+1
        if(c%2!=0):
            Plain_Text= Plain_Text.join([str(i) for i in P])
    print(Plain_Text)
    
            
def encrypt(text):
   
    n=len(text)
    Text=list(text)
    key={1:'EURUSHOLMES',2:'MARYWATSON',3:'IRENE',4:'SHERLOCKED',5:'REICHENBACHFALL'}
    val=list(key.values())
    for k in val:
        Plain_Text=''
        m=len(k)
        temp=list(k)
        key_extn=temp
        P=[]
        for i in range(n-m):
            key_extn.append(temp[i])
        for i in range(n):
            c=(ord(Text[i])+ord(key_extn[i]))%26
            P.append(chr(c+65))
        
        
        Plain_Text= Plain_Text.join([str(i) for i in P])
        print(Plain_Text)


if __name__=="__main__":
    text=input('Enter the text : ')
    k=int(input('Enter 1 to encrypt, 2 to decrypt : '))
    if(k==1):
        encrypt(text)
    elif(k==2):
        decrypt(text)
        
    
    
    
