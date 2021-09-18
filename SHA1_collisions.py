import hashlib,os

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
    #creating a new dictionary where the key and value are swapped
    #This is done find hashes that corresponds to more than one message
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
    #Creating 2* 2^(8/2) i.e. 32 random 8 byte messages to get a collision in the first 8 bits of sha1 hash
    #Getting a collision with more than 50% chance is a consequence of the birthday paradox
    for i in range(32):
        m=os.urandom(8)
        sha1(m)
    find_collision()
    
    
