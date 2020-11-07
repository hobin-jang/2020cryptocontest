normal_fre=[8.12,1.49,2.71,4.32,12.02,2.30,2.03,5.92,7.31,0.10,0.69,3.98,
      2.61,6.95,7.68,1.82,0.11,6.02,6.28,9.10,2.88,1.11,2.09,0.17,2.11,0.07]
#normal_fre : alphabet frequency 백분율 (참조: http://pi.math.cornell.edu/)

def log(n):
   import math
   result=math.log(n,2)
   return result

#log(n)=밑이 2인 로그 값

def IML(P):
   sum_fre=0                     #sum_fre: P에 대한 IML값
   for j in range(26):
       hat=(P.count(j)/len(P))            #observed frequency 계산
       
       frequency=(normal_fre[j]/100)           #alphabet frequency
       
       sum_fre+=(-1)*(hat*log(frequency))            #IML 식 계산
   return sum_fre                                       

f=open('no.1.txt','r')                 # no.1.txt : 주어진 암호문 복사한 text
s=f.read()
s=s.replace(' ','')                      # s: 공백 없는 암호문 전체
f.close()

cipher=[]                            #계산을 위해 암호문을 257블럭 (5글자)로 나눈다.

for i in range(len(s)//5):              #len(s)=1285=5*257
    
   c=s[5*i:5*(i+1)]                         #c: 주어진 암호문 s를 5글자씩 나눈다.
   
   Ascii=[]                                    # Ascii: 암호문을 mod26에 대한 수(A:0 ~ Z:25)로 변환
   for j in range(len(c)):
       Ascii.append(ord(c[j])-ord('A'))
   cipher.append(Ascii)                  #cipher: 주어진 암호문을 5글자씩 나눈 257블럭이 들어있다.
   
def dec(K):                          #dec(K): 복호화 key의 열이 K일 때, 평문 계산 함수
    P=[]
    for i in range(257):             #i번째 블럭 행렬 계산
        
        text=0                           #text: i번째 블럭과 K를 계산한 결과
        for j in range(5):
            text+=((cipher[i][j]*K[j]))    
        P.append(sum1%26)
    return P                          #P: 암호문 257블럭과 복호화 key의 열 K를 계산한 결과
        
lexi=[]                           #lexi: 복호화 key의 열을 사전 순으로 정렬 

for i in range(26):
   for j in range(26):
       for k in range(26):
           for l in range(26):
               for t in range(26):
                   lexi.append([i,j,k,l,t])


result=[]
for x in lexi:
    judge1=[x[0]%2,x[1]%2,x[2]%2,x[3]%2,x[4]%2]
    judge2=[x[0]%13,x[1]%13,x[2]%13,x[3]%13,x[4]%13]
    if any(judge1)==False or any(judge2)==False:
       continue                                     #복호화 key의 inverse 존재하는 경우만 계산
   
    else:
        result.append([IML(dec(x)),x])             #복호화 key의 열 x와 x의 IML값을 result에 저장
        
result.sort()                                      #IML값에 따라 오름차순 정렬
for i in range(5):
    print(result[i])                               #IML값 낮은 5가지 경우 출력 (복호화 key)

from itertools import permutations         
a=[0,1,2,3,4]
per=list(permutations(a,5))                       #per: 조합 120가지를 정함

K=result[:5]                                     # K: 복호화 key 

list1=[]                                         #list1: 복호화 key의 열들을 조합한 list
for p in per:
    list1.append(K[p[0]])
    list1.append(K[p[1]])
    list1.append(K[p[2]])
    list1.append(K[p[3]])
    list1.append(K[p[4]])
    P=''                                          #P: 복호화한 평문
    for i in range(257):
        for j in range(5):
            answer=0                             
            for k in range(5):
                answer+=(cipher[i][k]*list1[j][k])       #answer: 암호문과 복호화 key 계산한 결과 
            answer=answer%26
            P+=(chr(answer+65))                          #answer값을 알파벳으로 변환
    print(P)                                             #해당 조합을 이용한 평문 출력
    print('')
    print(list1)                                         # 해당 복호화 key 출력
    print('')
    list1=[]

