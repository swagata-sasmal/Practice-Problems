// Program for Generalised Mersenne Prime reduction
// Cryptography Implementation Course Instructor : Prof. Sabyasachi Karati
// Swagata Sasmal ( M.Tech CrS, CrS2024)

#include<stdio.h>

void convertC2I(unsigned char *, unsigned long int*);
void add(unsigned long int*, unsigned long int*, unsigned long int *);
void convertI2C(unsigned long int*, unsigned char*, int size);
void multiplication(unsigned long int*, unsigned long int*,int, unsigned long int*);
void Mersenne_Reduction_pdt(unsigned long int*);


void main(){
    // taking a and b as two numbers close to and less than p = 2^251 - 9 , generated randomly in pari gp using random()
    unsigned char a_8[32] = {108, 55, 193, 34, 72, 24, 206, 221, 51, 191, 137, 123, 91, 201, 124, 178, 143, 123, 117, 245, 217, 202, 133, 136, 81, 105, 135, 56, 134, 79, 87, 4};
    unsigned char b_8[32] = {180, 51, 21, 93, 91, 224, 20, 147, 74, 167, 251, 243, 158, 232, 148, 93, 152, 31, 44, 241, 127, 238, 28, 30, 155, 101, 65, 88, 218, 139, 106};
    unsigned long int a_26[10], b_26[10],sum_26[11];
    unsigned long int c_26[20];
    unsigned char c_8[64],sum_8[33];
    int i;
    
    convertC2I(a_8,a_26);
    printf("\n\n\n a in base 2^26 : ");
    for(i=0;i<10;i++)
        printf("%lu ",a_26[i]);
        
    convertC2I(b_8,b_26);
    printf("\n\n\n b in base 2^26 : ");
    for(i=0;i<10;i++)
        printf("%lu ",b_26[i]);
    
    add(a_26,b_26,sum_26);
    printf("\n\n\n Sum of in base 2^26 : ");
    for(i=0;i<10;i++)
        printf("%lu ",sum_26[i]);
        
    convertI2C(sum_26,sum_8,11);
    printf("\n\n\n Sum of in base 2^8 : ");
    for(i=0;i<33;i++)
        printf("%hu ",sum_8[i]);
    
        
    multiplication(a_26,b_26,10,c_26);
    printf("\n\n\n Product of a and b in base 2^26 : ");
    for(i=0;i<20;i++)
        printf("%lu ",c_26[i]);
        
    convertI2C(c_26,c_8,64);
    printf("\n\n\n Product of a and b in base 2^8 : ");
    for(i=0;i<64;i++)
        printf("%hu ",c_8[i]);
    
    Mersenne_Reduction_pdt(c_26);
    /* Mersenne_Reduction_sum(sum_26); */
    
}

void convertC2I(unsigned char x_8[], unsigned long int x_26[]){
    
    x_26[0] = x_8[0] | (x_8[1] << 8 ) | (x_8[2] << 16) | ((x_8[3] & 0x3) << 24) ;
    x_26[1] = (x_8[3] >> 2) | (x_8[4] << 6) | (x_8[5] << 14) | ((x_8[6] & 0xF) << 22);
    x_26[2] = (x_8[6] >> 4) | (x_8[7] << 4) | (x_8[8] << 12) | ((x_8[9] & 0x3F) << 20);
    x_26[3] = (x_8[9] >> 6) | (x_8[10] << 2) | (x_8[11] << 10) | (x_8[12] << 18);
    
    x_26[4] = x_8[13] | (x_8[14] << 8 ) | (x_8[15] << 16) | ((x_8[16] & 0x3) << 24) ;
    x_26[5] = (x_8[16] >> 2) | (x_8[17] << 6) | (x_8[18] << 14) | ((x_8[19] & 0xF) << 22);
    x_26[6] = (x_8[19] >> 4) | (x_8[20] << 4) | (x_8[21] << 12) | ((x_8[22] & 0x3F) << 20);
    x_26[7] = (x_8[22] >> 6) | (x_8[23] << 2) | (x_8[24] << 10) | (x_8[25] << 18);
    
    x_26[8] = x_8[26] | (x_8[27] << 8 ) | (x_8[28] << 16) | ((x_8[29] & 0x3) << 24) ;
    x_26[9] = (x_8[29] >> 2) | (x_8[30] << 6) | (x_8[31] << 14) ;
     
}

void add(unsigned long int a[], unsigned long int b[], unsigned long int c[]) {
    int i; 
    unsigned long int carry=0;
    for(i=0;i<10;i++)
        c[i] = a[i] + b[i] ;
    c[11]=0;
    
    for(i=0;i<10;i++){
        carry = c[i] >> 26;
        c[i]  = c[i] & 0x3FFFFFF ;
        c[i+1] = c[i+1] + carry;
    }
}

void convertI2C(unsigned long int x_26[], unsigned char x_8[], int size){
    int i,j;
    j=0;
    if(size==64){
    for(i=0 ; i < 64 ; i=i+13){
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
    
    j=j+4;
    if(j==20)
        break;
    }
        
    }
    j=0;
    for(i=0;i<26;i=i+13){
    x_8[0+i] = x_26[0+j] & 0xFF ;
    x_8[1+i] = (x_26[0+j] >> 8) & 0xFF ;
    x_8[2+i] = (x_26[0+j] >>16) & 0xFF ;
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
    
    j=j+4;
    }
    
    x_8[26] = x_26[8] & 0xFF;
    x_8[27] = (x_26[8] >> 8) & 0xFF;
    x_8[28] = (x_26[8] >> 16) & 0xFF;
    x_8[29] = (x_26[8] >> 24) | ((x_26[9] & 0x3F) << 2) ;
    x_8[30] = (x_26[9] >> 6) & 0xFF;
    x_8[31] = (x_26[9] >> 14) & 0xFF;
    x_8[32] = (x_26[9] >> 22) | ((x_26[10] & 0xF) << 4);
    
}

void multiplication(unsigned long int a[], unsigned long int b[],int size, unsigned long int c_26[]){
    unsigned long long int t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,s0,s1,s2,s3,s4,s5,s6,s7,s8,s9;
    int i;
    unsigned long long int c[20];
    
    t0 = a[0]*b[0] ; t1 = a[1]*b[1] ;  t2 = a[2]*b[2] ; t3 = a[3]*b[3] ; t4 = a[4]*b[4] ;
    t5 = (a[0] + a[1])*(b[0] + b[1]) - t1 - t0 ;
    t6 = (a[0] + a[2])*(b[0] + b[2]) - t2 - t0 ;
    t7 = (a[0] + a[3])*(b[0] + b[3]) - t3 - t0 ;
    t8 = (a[0] + a[4])*(b[0] + b[4]) - t4 - t0 ;
    
    s1 = (a[1] + a[2])*(b[1] + b[2]) - t2 - t1 ;
    s2 = (a[1] + a[3])*(b[1] + b[3]) - t3 - t1 ;
    s3 = (a[1] + a[4])*(b[1] + b[4]) - t4 - t1 ;
    s4 = (a[2] + a[3])*(b[2] + b[3]) - t3 - t2 ;
    s5 = (a[2] + a[4])*(b[2] + b[4]) - t4 - t2 ;
    s6 = (a[3] + a[4])*(b[3] + b[4]) - t4 - t3 ;
    
    c[0] = t0 ;                 c[5] = s3 + s4 ;
    c[1] = t5 ;                 c[6] = s5 + t3 ;
    c[2] = t1 + t6 ;            c[7] = s6 ;
    c[3] = t7 + s1 ;            c[8] = t4 ;          
    c[4] = t8 + s2 + t2;
    
    //...................................................
    
    t0 = a[5]*b[5] ; t1 = a[6]*b[6] ;  t2 = a[7]*b[7] ; t3 = a[8]*b[8] ; t4 = a[9]*b[9] ;
    t5 = (a[5] + a[6])*(b[5] + b[6]) - t1 - t0 ;
    t6 = (a[5] + a[7])*(b[5] + b[7]) - t2 - t0 ;
    t7 = (a[5] + a[8])*(b[5] + b[8]) - t3 - t0 ;
    t8 = (a[5] + a[9])*(b[5] + b[9]) - t4 - t0 ;
    
    s1 = (a[6] + a[7])*(b[6] + b[7]) - t2 - t1 ;
    s2 = (a[6] + a[8])*(b[6] + b[8]) - t3 - t1 ;
    s3 = (a[6] + a[9])*(b[6] + b[9]) - t4 - t1 ;
    s4 = (a[7] + a[8])*(b[7] + b[8]) - t3 - t2 ;
    s5 = (a[7] + a[9])*(b[7] + b[9]) - t4 - t2 ;
    s6 = (a[8] + a[9])*(b[8] + b[9]) - t4 - t3 ;
    
    c[10] = t0 ;                 c[15] = s3 + s4 ;
    c[11] = t5 ;                 c[16] = s5 + t3 ;
    c[12] = t1 + t6 ;            c[17] = s6 ;
    c[13] = t7 + s1 ;            c[18] = t4 ;          
    c[14] = t8 + s2 + t2;
    
    //................................................
    
    t0 = a[0]*b[0] ; t1 = a[1]*b[1] ;  t2 = a[2]*b[2] ; t3 = a[3]*b[3] ; t4 = a[4]*b[4] ;
    s0 = a[5]*b[5] ; s1 = a[6]*b[6] ;  s2 = a[7]*b[7] ; s3 = a[8]*b[8] ; s4 = a[9]*b[9] ;
    
    t5 = (a[0] + a[5])*(b[0] + b[5]) - s0 - t0 ;
    t6 = (a[0] + a[6])*(b[0] + b[6]) - s1 - t0 ;
    t7 = (a[0] + a[7])*(b[0] + b[7]) - s2 - t0 ;
    t8 = (a[0] + a[8])*(b[0] + b[8]) - s3 - t0 ;
    t9 = (a[0] + a[9])*(b[0] + b[9]) - s4 - t0 ;
    
    s5 = (a[1] + a[5])*(b[1] + b[5]) - s0 - t1 ;
    s6 = (a[1] + a[6])*(b[1] + b[6]) - s1 - t1 ;
    s7 = (a[1] + a[7])*(b[1] + b[7]) - s2 - t1 ;
    s8 = (a[1] + a[8])*(b[1] + b[8]) - s3 - t1 ;
    s9 = (a[1] + a[9])*(b[1] + b[9]) - s4 - t1 ;
    
    unsigned long long int r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,p0,p1,p2,p3,p4;
    
    r0 = (a[2] + a[5])*(b[2] + b[5]) - s0 - t2 ;
    r1 = (a[2] + a[6])*(b[2] + b[6]) - s1 - t2 ;
    r2 = (a[2] + a[7])*(b[2] + b[7]) - s2 - t2 ;
    r3 = (a[2] + a[8])*(b[2] + b[8]) - s3 - t2 ;
    r4 = (a[2] + a[9])*(b[2] + b[9]) - s4 - t2 ; 
    
    p0 = (a[3] + a[5])*(b[3] + b[5]) - s0 - t3 ;
    p1 = (a[3] + a[6])*(b[3] + b[6]) - s1 - t3 ;
    p2 = (a[3] + a[7])*(b[3] + b[7]) - s2 - t3 ;
    p3 = (a[3] + a[8])*(b[3] + b[8]) - s3 - t3 ;
    p4 = (a[3] + a[9])*(b[3] + b[9]) - s4 - t3 ;
    
    c[5] = c[5] + t5 ;
    c[6] = c[6] + s5 + t6 ;
    c[7] = c[7] + t7 + s6 + r0;
    c[8] = c[8] + t8 + s7 + r1 + p0;
    
    r5 = (a[4] + a[5])*(b[4] + b[5]) - s0 - t4 ;
    r6 = (a[4] + a[6])*(b[4] + b[6]) - s1 - t4 ;
    r7 = (a[4] + a[7])*(b[4] + b[7]) - s2 - t4 ;
    r8 = (a[4] + a[8])*(b[4] + b[8]) - s3 - t4 ;
    r9 = (a[4] + a[9])*(b[4] + b[9]) - s4 - t4 ; 
    
    c[9] = t9 + s8 + r2 + p1 + r5;
    c[10] = c[10] + s9 + r3 + p2 + r6;
    c[11] = c[11] + r4 + p3 + r7;
    c[12] = c[12] + p4 + r8;
    c[13] = c[13] + r9;
    
    //................................................................
    c[19]=0;
    unsigned long int carry;
    for(i=0 ; i< 19 ; i++){
        carry = (c[i] >> 26);
        c_26[i] = c[i] & 0x3FFFFFF;
        c[i+1] = c[i+1] + carry;
    }
    c_26[19] = c[19];
    
}

void Mersenne_Reduction_pdt(unsigned long int c_26[]){
    int i;
    unsigned long int c0[10],c1[11];
    
    //....... C mod p = C0 + 9 * C1........... Getting the two halves C0 and C1
    for(i=0;i<9;i++)
        c0[i] = c_26[i];
    c0[9] = c_26[9] & 0x1FFFF ;
    
    for(i=0;i<10;i++)
         c1[i] = (c_26[9+i] >> 17) | ((c_26[10+i] & 0x1FFFF) << 9) ;
         
    c1[10]=0;
    
    unsigned long int carry = 0;
    for(i=0;i<10;i++)
        c1[i] = c1[i] * 9 ;
    for(i=0;i<10;i++){
        carry = (c1[i] >> 26);
        c1[i] = c1[i] & 0x3FFFFFF;
        c1[i+1] += carry;
    }
    
    unsigned long int value[12];
    carry =0;
    for(i=0;i<10;i++)
        value[i] = c0[i] + c1[i];
    value[10] = c1[10];
    for(i=0;i<11;i++){
        carry = value[i] >> 26;
        value[i] = value[i] & 0x3FFFFFF;
        value[i+1]= value[i+1] + carry;
    }
    
    //printing the result after one round of mersenne prime reduction. here we wont need to repeat.
    printf("\n\n\n The product modulo p is :  ");
    for(i=0;i<11;i++)
        printf("%lu ",value[i]);
}
    
/*void Mersenne_Reduction_sum(unsigned long int s[]){
    //sum is at most 252 bits long given that a and b are at most 251 bits
    // s is an array of length 11
    // we need to split it to 251 bits + the rest 
    unsigned long int s0[10];
    int i;
    for(i=0;i<9;i++)
        s0[i]= s[i];
    s0[9]= (s[9] & 0x1FFFF);
    unsigned long int s1[10],carry;
    for(i=0;i<10;i++)
        s1[i]= 0;
    s1[0] = (s[9] >> 17) | ((s[10] & 0x1FF) << 17);
    s1[0] = s1[0] * 9;
    carry = s1[0] >> 26 ;
    s1[0] = s1[0] & 0x3FFFFFF;
    s1[1] = carry;
    unsigned long int result[11];
    for(i=0;i<11;i++)
        result[i]= 0;
    add(s0,s1,result);
    printf("\n\n\n The sum modulo p is : ");
    for(i=0;i<11;i++)
        printf("%lu ",result[i]);
}*/






