// Program for Barrett reduction
// Swagata Sasmal ( M.Tech CrS, CrS2024)

#include<stdio.h>
#include<math.h>

void convertC2I(unsigned char *, unsigned long int*);
void add(unsigned long int*, unsigned long int*, unsigned long int *);
void convertI2C(unsigned long int*, unsigned char*, int size);
void multiplication(unsigned long int*, unsigned long int*,int, unsigned long int*);
void Barrett_Reduction(unsigned long int*);


void main(){
    // taking a and b as two numbers close to n = 127703548307208031630827729618994936071 , generated randomly in pari gp using random()
    unsigned char a_8[16] = {56, 6, 81, 186, 169, 151, 84, 184, 130, 200, 163, 133, 82, 128, 112, 52};
    unsigned char b_8[16] = {157, 126, 135, 118, 56, 6, 11, 208, 111, 68, 129, 113, 26, 69, 3, 46};
    unsigned long int a_26[5], b_26[5],sum_26[6];
    unsigned long int c_26[10];
    unsigned char c_8[32],sum_8[17];
    int i;
    
    convertC2I(a_8,a_26);
    printf("\n\n\n a in base 2^26 : ");
    for(i=0;i<5;i++)
        printf("%lu ",a_26[i]);
        
    convertC2I(b_8,b_26);
    printf("\n\n\n b in base 2^26 : ");
    for(i=0;i<5;i++)
        printf("%lu ",b_26[i]);
    
    add(a_26,b_26,sum_26);
    printf("\n\n\n Sum of in base 2^26 : ");
    for(i=0;i<6;i++)
        printf("%lu ",sum_26[i]);
        
    convertI2C(sum_26,sum_8,11);
    printf("\n\n\n Sum of in base 2^8 : ");
    for(i=0;i<17;i++)
        printf("%hu ",sum_8[i]);
    
        
    multiplication(a_26,b_26,10,c_26);
    printf("\n\n\n Product of a and b in base 2^26 : ");
    for(i=0;i<10;i++)
        printf("%lu ",c_26[i]);
        
    convertI2C(c_26,c_8,32);
    printf("\n\n\n Product of a and b in base 2^8 : ");
    for(i=0;i<32;i++)
        printf("%hu ",c_8[i]);
    
    Barrett_Reduction(c_26);
    
}

void convertC2I(unsigned char x_8[], unsigned long int x_26[]){
    
    x_26[0] = x_8[0] | (x_8[1] << 8 ) | (x_8[2] << 16) | ((x_8[3] & 0x3) << 24) ;
    x_26[1] = (x_8[3] >> 2) | (x_8[4] << 6) | (x_8[5] << 14) | ((x_8[6] & 0xF) << 22);
    x_26[2] = (x_8[6] >> 4) | (x_8[7] << 4) | (x_8[8] << 12) | ((x_8[9] & 0x3F) << 20);
    x_26[3] = (x_8[9] >> 6) | (x_8[10] << 2) | (x_8[11] << 10) | (x_8[12] << 18);
    x_26[4] = x_8[13] | (x_8[14] << 8 ) | (x_8[15] << 16);
    
}

void add(unsigned long int a[], unsigned long int b[], unsigned long int c[]) {
    int i; 
    unsigned long int carry=0;
    for(i=0;i<5;i++)
        c[i] = a[i] + b[i] ;
    c[5]=0;
    
    for(i=0;i<5;i++){
        carry = c[i] >> 26;
        c[i]  = c[i] & 0x3FFFFFF ;
        c[i+1] = c[i+1] + carry;
    }
}

void subtract(unsigned long int c_26[], unsigned long int rn[],unsigned long int t[]){
    int i;
    unsigned long int c_in,c_out;
    c_in = 0 ;
    unsigned long int base = pow(2,26);
    c_out = 0;
    for(i=0;i<9;i++){
        if(c_in == 0){
            if(c_26[i] < rn[i]){
                c_out = 1;
                t[i] = c_26[i] + base - rn[i] - c_in;
            }
            else if(c_26[i] >= rn[i]){
                t[i] = c_26[i] - rn[i];
                c_out = 0;
            }
        }
        else if(c_in == 1){
            if(c_26[i] < rn[i]){
                c_out = 1;
                t[i] = c_26[i] + base - rn[i] - c_in;
                
            }
            else if(c_26[i] = rn[i]){
                t[i] = c_26[i] - rn[i] - c_in;
                c_out = 1;
            }
        }
        
        c_in = c_out;
        
    }
    t[9] = c_26[i] - rn[i] - c_in ;
       
        
        
}

void convertI2C(unsigned long int x_26[], unsigned char x_8[], int size){
    int i,j;
    j=0;
    if(size == 32){
    for(i=0 ; i < 26 ; i=i+13){
    x_8[0+i] = x_26[0+j] & 0xFF ;
    x_8[1+i] = (x_26[0+j] >> 8) & 0xFF ;
    x_8[2+i] = (x_26[0+j] >> 16) & 0xFF ;
    x_8[3+i] = (x_26[0+j] >> 24) | ((x_26[1+j] & 0x3F) << 2) ;
    x_8[4+i] = (x_26[1+j] >> 6) & 0xFF;
    x_8[5+i] = (x_26[1+j] >> 14) & 0xFF;
    x_8[6+i] = (x_26[1+j] >> 22) | ((x_26[2+j] & 0xF) << 4);
    x_8[7+i] = (x_26[2+j] >> 4) & 0xFF;
    x_8[8+i] = (x_26[2+j] >> 12) & 0xFF;
    x_8[9+i] = (x_26[2+j] >> 20) | ((x_26[3+j] & 0x3) << 6);
    x_8[10+i] = (x_26[3+j] >> 2) & 0xFF;
    x_8[11+i] = (x_26[3+j] >> 10) & 0xFF;
    x_8[12+i] = (x_26[3+j] >> 18) ;
    
    j=j+4;}
    
    x_8[26] = x_26[8] & 0xFF;
    x_8[27] = (x_26[8] >> 8) & 0xFF;
    x_8[28] = (x_26[8] >> 16) & 0xFF;
    x_8[29] = (x_26[8] >> 24) | ((x_26[9] & 0x3F) << 2) ;
    x_8[30] = (x_26[9] >> 6) & 0xFF;
    x_8[31] = (x_26[9] >> 14) & 0xFF;
    }
    
    j=0;
    
    x_8[0] = x_26[0] & 0xFF ;
    x_8[1] = (x_26[0] >> 8) & 0xFF ;
    x_8[2] = (x_26[0] >>16) & 0xFF ;
    x_8[3] = (x_26[0] >> 24) | ((x_26[1] & 0x3F) << 2) ;
    x_8[4] = (x_26[1] >> 6) & 0xFF;
    x_8[5] = (x_26[1] >> 14) & 0xFF;
    x_8[6] = (x_26[1] >> 22) | ((x_26[2] & 0xF) << 4);
    x_8[7] = (x_26[2] >> 4) & 0xFF;
    x_8[8] = (x_26[2] >> 12) & 0xFF;
    x_8[9] = (x_26[2] >> 20) | ((x_26[3] & 0x3) << 6);
    x_8[10] = (x_26[3] >> 2) & 0xFF;
    x_8[11] = (x_26[3] >> 10) & 0xFF;
    x_8[12] = (x_26[3] >> 18);
    x_8[13] = x_26[4] & 0xFF;
    x_8[14] = (x_26[4] >> 8) & 0xFF;
    x_8[15] = (x_26[4] >> 16) & 0xFF;
    x_8[16] = (x_26[4] >> 24) | ((x_26[5] & 0x3F) << 2) ;
}

void multiplication(unsigned long int a[], unsigned long int b[],int size, unsigned long int c_26[]){
    unsigned long long int t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,s0,s1,s2,s3,s4,s5,s6;
    int i;
    unsigned long long int c[20];
    
    t0 = a[0]*b[0] ; t1 = a[1]*b[1] ;  t2 = a[2]*b[2] ; t3 = a[3]*b[3] ; t4 = a[4]*b[4] ;
    t5 = (a[0] + a[1])*(b[0] + b[1]) - t1 - t0 ;    // a0*b1 + a1*b0
    t6 = (a[0] + a[2])*(b[0] + b[2]) - t2 - t0 ;    // a0*b2 + a2*b0
    t7 = (a[0] + a[3])*(b[0] + b[3]) - t3 - t0 ;    // a0*b3 + a3*b0
    t8 = (a[0] + a[4])*(b[0] + b[4]) - t4 - t0 ;    // a0*b4 + a4*b0
    
    s1 = (a[1] + a[2])*(b[1] + b[2]) - t2 - t1 ;    // a1*b2 + b1*a2
    s2 = (a[1] + a[3])*(b[1] + b[3]) - t3 - t1 ;    // a1*b3 + b1*a3
    s3 = (a[1] + a[4])*(b[1] + b[4]) - t4 - t1 ;    // a1*b4 + b1*a4
    s4 = (a[2] + a[3])*(b[2] + b[3]) - t3 - t2 ;    // a2*b3 + b2*a3
    s5 = (a[2] + a[4])*(b[2] + b[4]) - t4 - t2 ;    // a2*b4 + b2*a4
    s6 = (a[3] + a[4])*(b[3] + b[4]) - t4 - t3 ;    // a3*b4 + b3*a4
    
    c[0] = t0 ;                 c[5] = s3 + s4 ;
    c[1] = t5 ;                 c[6] = s5 + t3 ;
    c[2] = t1 + t6 ;            c[7] = s6 ;
    c[3] = t7 + s1 ;            c[8] = t4 ;          
    c[4] = t8 + s2 + t2;
    
    //................................................................
    c[9]=0;
    unsigned long int carry;
    for(i=0 ; i<9 ; i++){
        carry = (c[i] >> 26);
        c_26[i] = c[i] & 0x3FFFFFF;
        c[i+1] = c[i+1] + carry;
    }
    c_26[9] = c[9];
    
}


void Barrett_Reduction(unsigned long int c_26[]){
    int i,j;
    unsigned long int base = pow(2,26);
    unsigned long int n[] = {62601479, 20279032, 2380, 3009662, 6296271,0,0,0,0,0};
    //................PRE-COMPUTATION......................................
    int l = 5;
    //compute the factor T = floor(base ^ 2l / n) where 2l is the length of c_26. Here l is 5.
    unsigned long int T[] = {27292167, 14944148, 16792657, 35305346, 44191816, 10,0,0,0,0} ;
  
    
    //...............REDUCTION of C=A*B modulo n...............................................
    unsigned long int Q[10] , P[20], R[20];
    
    // We need to compute Q as floor(C / base ^ (l-1)) that is discard 26(l-1) least significant bits of C
    
    for(i=0;i<l;i++){
        Q[i] = c_26[l-1 +i];
    }
    for(i=l;i<10;i++)
        Q[i] = 0;
        
    //compute Q*T
    multiplication(Q,T,10,P);
    
    //compute S as floor( P / base ^(l+1)) i.e discard 26(l+1)least significant bits of P
    for(i=0;i<20;i++){
        if(l+1+i >= 20 )
            break;
        R[i] = P[l+1+i];
    }
    for(j=i;j<20;j++)
        R[j]=0;
    unsigned long int result[20];
    multiplication(Q,n,10,result);
    unsigned long int result_1[20];
    subtract(c_26,result,result_1);
    //compute result_1 (mod base ^ l+1) i.e take the first 26(l+1) bits of result_1
    unsigned long int result_2[10];
    for(i=0;i<10;i++)
        result_2[i] = 0 ;
    for(i=0;i<l+1;i++)
        result_2[i] = result_1[i] ;
    int flag = 0;
    for(i=0;i<10;i++){
        if(result_2[9-i] > n[9-i]){
            flag=1;
            break;
        }
    }
    unsigned long int result_3[10];
    for(i=0;i<10;i++)
        result_3[i] = 0 ;
    printf("\n\n\n The product modulo n is :  ");
    if(flag==1){
        subtract(result_2,n,result_3);
        for(i=0;i<10;i++){
            printf("%lu ",result_3[i]);
        }
    }
    else{
        for(i=0;i<10;i++)
            printf("%lu ",result_2[i]);
    }
}  
