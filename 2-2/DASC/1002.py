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
    print(' '*(4-i),'*'*(2*(i+1)-1),sep="")
    
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
        sum+=i**2
    return sum

print(sum_sq(int(input())))

#04 약수 구하기
def sol(num):
    lst = []
    for i in range(1,(num+1)//2+1):
        if num%i==0:
            lst.append(i) 
    lst.append(num)
    return lst

print(sol(int(input())))

#05 1부터 10,000까지 8의 갯수
def count8(num):
    cnt = 0
    for i in range(8,num+1):
            cnt+= str(i).count('8')
    return cnt

print(count8(10000))

#클래스 연습
class test:
    __a = 0
    def te(self):
        self.count = 100

class Counter(test):
    def __init__(self, n = 0):
        self.count = n
    def reset(self):
        self.count = 0
    def increment(self):
        self.count += 1
    def get(self):
        return self.count
    def set(self, n):
        count = n
    def tt(self):
        __a = 10
        return __a
    
a = Counter(30)
b = Counter()

for i in range(50):
    b.increment()
    
print(a.get())
print(b.get())

a.te()

print(a.get())
print(a.tt())

#pandas,numpy
import numpy as np
import pandas as pd

dic = {'city': ['서울', '부산', '대전', '대구', '광주'],
        'year': [2017, 2017, 2018, 2018, 2018],
        'temp': [18, 20, 19, 21, 20]}
data = pd.DataFrame(dic)
data.index = ['1','2','3','4','5'] 
data.columns = ['도시','연도','날씨']
cars = [50,40,20,30,10]
data['car'] = cars  #추가
data['high'] = data.car >= 30
data.drop('high',1)  #삭제
print(data,end ="\n\n\n")

f = lambda x: x.max() - x.min()
df = pd.DataFrame(np.arange(12).reshape(4, 3), 
                  columns=['A', 'B', 'C'], index=['a', 'b', 'c', 'd'])

print(df,end ="\n\n\n")
df[df<5]=0
print(df.apply(f, 1),end ="\n\n\n") 

#데이터 처리
import numpy as np
import matplotlib.pyplot as plt

!dir #현재 디랙토리
!curl http://opentechschool.github.io/python-data-intro/files/radishsurvey.txt\
    -o ./data/radishsurvey.txt
dict = {'name':[],
        'vote':[]
       }
vote = {}
with open("./data/radishsurvey.txt") as file:
    for line in file:  
        parts = line.strip().replace("  "," ").split(" - ")
        name = parts[0].capitalize()
        v = parts[1].capitalize()
        
        if name not in dict['name']:
            dict['name'].append(name)
            dict['vote'].append(v)
        
        if v not in vote:
            vote[v] = 1
        else:
            vote[v] += 1

data1 = pd.DataFrame(dict)
data2 = pd.DataFrame(list(vote.items()),columns=['Radish', 'Voted'])
print(data2)
print('\n\n',data1,sep="")

#그래프 그리기
%matplotlib inline
vals = [3,2,5,0,1]    
plt.plot(vals)    #x축은 자동으로 지정

plt.show()

#막대 그래프
names = []
votes = []

for radish in vote:
    names.append(radish)
    votes.append(vote[radish])

# The X axis can just be numbered 0,1,2,3...
x = np.arange(len(vote))

plt.bar(x, votes)
plt.xticks(x + 0.5, names, rotation=90)
plt.show()

#파일
from pandas import DataFrame, Series 
import pandas as pd 

with open("test.csv", "w") as f:
    f.write("a,b,c,d,message \n")
    f.write("1,2,3,4,hello \n")
    f.write("5,6,7,8,world \n")
    f.write("9,10,11,12,foo \n")
!type test.csv 
pd.read_csv('test.csv')

#폴더 관리
import os
!dir
#os.getcwd()
#os.mkdir('test1')#디렉토리 만들기
#os.rename('test1','chage_name')#디렉토리 이름바꾸기
#os.remove('./chage_name/outpu.csv')#삭제
#os.rmdir('change_name')
