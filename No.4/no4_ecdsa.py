
p=0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
a=-3
b=0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B
gx=0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296 
gy=0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5
n=0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551

h1=0xE06554818E902B4BA339F066967C0000DA3FCDA4FD7EB4EF89C124FA78BDA419
h2=0x5D2D3CEB7ABE552344276D47D36A8175B7AEB250A9BF0BF00E850CD23ECF2E43

r=0xF42A3ADB78BF22D9AA571FDFB0C93B415C8B50719C25B23F6F77DC299C01F2D7
s1=0x90A7F16EAFE3DB7923A07A6E8CF68F688100ABE3730A5416B37FA4BFBA7F5E22
s2=0x865BF221DD856B991EB6EF7EF1E0D263215FC8D7F2283A22C1F927ABDCC35B5B

qx=0xF44CD6277CED3F9CC2F29144CDBCFDC40F1BF556707ED8190E838D711A12EC03
qy=0x68B6FAF59BEC47A11D98800B4BE578CA4399B34EF94D6B602F5186D41B7430C9

def inverse_modn(a,n):
    r1,r2=a,n
    t1,t2=1,0
    while (r2>0):
        q=r1//r2
        r=(r1-q*r2)%n
        r1,r2=r2,r
        t=(t1-q*t2)%n
        t1,t2=t2,t
    return t1%n

def doubling(Qx,Qy,p,a):
    lambda_=((3*Qx*Qx+a)*inverse_modn(2*Qy,p))%p
    x_res=(lambda_**2-2*Qx)%p
    y_res=((Qx-x_res)*lambda_-Qy)%p
    result=(x_res,y_res)
    return result

def add(Px,Py,Qx,Qy,p):
    lambda__=(Qy-Py)*(inverse_modn(Qx-Px,p))%p
    x_res=(lambda__**2-Px-Qx)%p
    y_res=((Px-x_res)*lambda__-Py)%p
    result=(x_res,y_res)
    return result

####@@@@@#####
#n,h1,h2=256bit 이므로 z1=h1,z2=h2
# r1=x1=kG mod n
# r2=x2=k'G mod n
# r1=r2 => k'=-k
#d 계산
z1,z2=h1,h2
t=((-1)*((z1*s2)+(z2*s1)))%n
inv=inverse_modn(((s1+s2)*r)%n,n)
d=(t*inv)%n
print("private key:",hex(d))

#####@@@@@#####
#개인키 d가 맞는가
check=(gx,gy)
bin_d=bin(d)[2:]

for i in range(1,len(bin_d)):
    if bin_d[i]=='1':
        check=doubling(check[0],check[1],p,a)
        check=add(check[0],check[1],gx,gy,p)
    elif bin_d[i]=='0':
        check=doubling(check[0],check[1],p,a)

if qx==check[0] and qy==check[1]:
    print("d is right") 

#####@@@@@#####
#Q가 curve 위 점인가
if (qy**2)%p==(qx**3+a*qx+b)%p:
    print('Q is in curve')

#####@@@@@#####
#Q가 identity 아닌가
if doubling(qx,qy,p,a)!=(qx,qy):
    print('Q is not identity')

#####@@@@@#####
#n*Q=O 만족하는가
bin_n=bin(n)[2:]
gen=(qx,qy)
for i in range(1,len(bin_n)):
    if bin_n[i]=='1':
        gen=doubling(gen[0],gen[1],p,a)
        gen=add(gen[0],gen[1],qx,qy,p)
    elif bin_n[i]=='0':
        gen=doubling(gen[0],gen[1],p,a)

if add(gen[0],gen[1],qx,qy,p)[0]==qx:
    print("n*Q=O")

#####@@@@@#####
#n*G=O 만족하는가    
gen2=(gx,gy)
for i in range(1,len(bin_n)):
    if bin_n[i]=='1':
        gen2=doubling(gen2[0],gen2[1],p,a)
        gen2=add(gen2[0],gen2[1],gx,gy,p)
    elif bin_n[i]=='0':
        gen2=doubling(gen2[0],gen2[1],p,a)

if add(gen2[0],gen2[1],gx,gy,p)[0]==gx:
    print("n*G=O")

#####@@@@@#####
#r,s는 모두 n보다 작은가
if r<n and s1<n and s2<n:
    print("r,s1,s2 is in 1~(n-1)")

#####@@@@@#####
#서명 유효성 판단
w1=inverse_modn(s1,n)
w2=inverse_modn(s2,n)

u1=(z1*w1)%n
u2=(r*w1)%n

v1=(z2*w2)%n
v2=(r*w2)%n

str1=bin(u1)[2:]
str2=bin(u2)[2:]

str3=bin(v1)[2:]
str4=bin(v2)[2:]

if len(str1)>len(str2):
    while(len(str1)>len(str2)):
        str2='0'+str2

if len(str1)<len(str2):
    while(len(str1)<len(str2)):
        str1='0'+str1

if len(str3)>len(str4):
    while(len(str3)>len(str4)):
        str4='0'+str4

if len(str3)<len(str4):
    while(len(str3)<len(str4)):
        str3='0'+str3

R=add(gx,gy,qx,qy,p)
rx=R[0]
ry=R[1]

if str1[0]=='1':
    test=(gx,gy)
elif str2[0]=='1':
    test=(qx,qy)

#####@@@@@#####
#S1에 대해 판단
for i in range(1,len(str1)):
    if (str1[i]=='0' and str2[i]=='0' ):
        test=doubling(test[0],test[1],p,a)
    elif (str1[i]=='0' and str2[i]=='1'):
        test=doubling(test[0],test[1],p,a)
        test=add(test[0],test[1],qx,qy,p)
    elif (str1[i]=='1' and str2[i]=='0'):
        test=doubling(test[0],test[1],p,a)
        test=add(test[0],test[1],gx,gy,p)
    elif (str1[i]=='1' and str2[i]=='1'):
        test=doubling(test[0],test[1],p,a)
        test=add(test[0],test[1],rx,ry,p)

if test[0]%n==r%n:
    print('signature is valid on S1')
    
if str3[0]=='1':
    test2=(gx,gy)
elif str4[0]=='1':
    test2=(qx,qy)

#####@@@@@#####
#S2에 대해 판단
for i in range(1,len(str3)):
    if (str3[i]=='0' and str4[i]=='0' ):
        test2=doubling(test2[0],test2[1],p,a)
    elif (str3[i]=='0' and str4[i]=='1'):
        test2=doubling(test2[0],test2[1],p,a)
        test2=add(test2[0],test2[1],qx,qy,p)
    elif (str3[i]=='1' and str4[i]=='0'):
        test2=doubling(test2[0],test2[1],p,a)
        test2=add(test2[0],test2[1],gx,gy,p)
    elif (str3[i]=='1' and str4[i]=='1'):
        test2=doubling(test2[0],test2[1],p,a)
        test2=add(test2[0],test2[1],rx,ry,p)

if test2[0]%n==r%n:
    print('signature is valid on S2')


