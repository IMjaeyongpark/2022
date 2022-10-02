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
