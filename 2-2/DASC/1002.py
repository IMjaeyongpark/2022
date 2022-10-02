#함수
x,y = map(int,input().split())
def calc(x,y):
    return x+y,x-y,x*y,x/y

a,s,m,d =calc(x,y)
print('덧셈: {0}, 뺄셈: {1}, 곱셈: {2}, 나눗셈: {3}'.format(a,s,m,d))

def personal_info(**info):
    print('이름: {0}, 나이: {1}, 주소: {2}'.format(info['name'],info['age'],info['address']))
    for kw, arg in info.items():
          print('{0}: {1}'.format(kw,arg))
    
    

x = {'name': '홍길동','age':30,'address':'서울시 용산구 이촌동'}
personal_info(**x)

#01 별찍기

for i in range(5):
    print(' '*(4-i),'*'*(2*(i+1)-1))
    
#02 최대 최소
def get_max_min(data_list):
    return min(data_list), max(data_list)

lst = list(map(int,input().split()))
_min,_max = get_max_min(lst)
print('최소: {0}, 최대: {1}'.format(_min,_max))

#03 1부터 n까지 제곱의 합
def  sum_sq(num):
    sum = 0
    for i in range(1,num+1):
        sum+=i*i
    return sum

print(sum_sq(int(input())))

#04 약수 구하기
def sol(num):
    lst = []
    for i in range(1,num+1):
        if num%i==0:
            lst.append(i) 
    return lst

print(sol(int(input())))

#05 1부터 10,000까지 8의 갯수
def count8(num):
    cnt = 0
    for i in range(num+1):
        tmp = str(i)
        for n in tmp:
            if n == '8':
                cnt+=1
    return cnt

print(count8(10000))
