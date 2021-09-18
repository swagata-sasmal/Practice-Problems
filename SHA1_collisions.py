import hashlib,os

Msg_hash=[]
LookUp={}
LookUp_reverse={}

def sha1(msg):
    msg_digest = hashlib.sha1(msg).hexdigest()
    Msg_Hash = msg_digest[:2]
    Msg_hash.append(Msg_Hash)
    LookUp[msg]=Msg_Hash

def find_collision():
    LookUp_reverse={}
    collisions=0
    colliding_pairs=[]
    for key,value in LookUp.items():
        if value in LookUp_reverse.keys():
            LookUp_reverse[value].append(key)
        else:
            temp=[]
            temp.append(key)
            LookUp_reverse[value]= temp[:]
    
    for key,value in LookUp_reverse.items():
        if(len(value)==2):
            collisions=collisions+1
            colliding_pairs.append(value)
    print("No. of collisions :", collisions)
    print("Colliding pairs:",colliding_pairs)
        
if __name__=="__main__":

    for i in range(256):
        m=os.urandom(16)
        sha1(m)
    
    
    find_collision()
    
    
