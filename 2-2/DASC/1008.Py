!curl https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat \
    -o ./data/airports.dat
  
# 파일 확인
import csv
# f = open("./data/airports.dat")
f = open("./data/airports.dat"a, encoding='UTF-8')
for row in csv.reader(f):
    print(row[0:4])
    
!curl https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat \
    -o ./data/routes.dat
  
# 위도와 경도를 딕셔너리 변수에 담고 운행 거리를 계산하겠다. 먼저 위도 값을 확인한다.
latitudes = {} #위도
longitudes = {} #경도
apName = {}
f = open("./data/airports.dat", encoding='UTF-8')
for row in csv.reader(f):  #공항 ID를 key로 설정
    airport_id = row[0]
    latitudes[airport_id] = float(row[6])
    longitudes[airport_id] = float(row[7])
    apName[airport_id] = row[1]
apName

!pip install geopy

from geopy.distance import great_circle, geodesic
# great_circle((37, 127), (38, 129))
# dist = geodesic((37, 127), (38, 129))
# dist.km
distances = []
count = 0
f = open("./data/routes.dat")
for row in csv.reader(f):
    source_airport = row[3]
    dest_airport = row[5]
    if source_airport in latitudes and dest_airport in latitudes:
        source_lat = latitudes[source_airport]
        source_long = longitudes[source_airport]
        dest_lat = latitudes[dest_airport]
        dest_long = longitudes[dest_airport]
        distances.append(great_circle((source_lat,source_long),(dest_lat,dest_long)).km)   #.miles
        print("source :",apName[source_airport],"/","destination :", apName[dest_airport],"/","distances :",round(distances[count],3),"km")
        count += 1
        
import matplotlib.pyplot as plt
%matplotlib inline

plt.hist(distances, 100,facecolor='b')
plt.xlabel("Distance (km)")
plt.ylabel("Number of flights")

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from pandas import DataFrame, Series
from numpy.random import randn
%matplotlib inline

plt.plot(np.arange(0,30,3))
fig = plt.figure() 
ax1 = fig.add_subplot(2, 2, 1) 
ax2 = fig.add_subplot(2, 2, 2) 
ax3 = fig.add_subplot(2, 2, 3)
ax1.hist(np.random.randn(200), bins=20, color='k', rwidth=0.5)    # 히스토그램
ax2.scatter(np.arange(30), np.arange(30) + 3*np.random.randn(30))    #산점도(스캐터플롯)
ax3.plot(np.arange(10),np.random.randn(10))    #랜덤넘버 그래프
fig
plt.subplots_adjust(left=None, bottom=None, right=None, top=None,
                wspace=None, hspace=None) # subplot 간의 간격을 조정하는 함수 _adjust()
# wspace, hspace: width and height between the subplots
# left, right, top, bottom: sides of the subplots

# 2*2 =4 개의 그림을 그리는 예
fig, axes = plt.subplots(2, 2, sharex=True, sharey=True)
for i in range(2):
    for j in range(2):
        axes[i, j].hist(np.random.randn(500), bins=50, color='k', alpha=0.5)
plt.subplots_adjust(wspace=0, hspace=0)

# 1000개의 랜덤넘버 (정규분포)의 누적 값을 그리는 예
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.plot(randn(1000).cumsum(), 'k', label='one')
ax.plot(randn(1000).cumsum(), 'b--', label='two')
ax.plot(randn(1000).cumsum(), 'r.', label='three')

ax.legend(loc='best') 

# 일반 도형을 그리는 함수도 제공
fig = plt.figure(figsize=(5,5))
ax = fig.add_subplot(1, 1, 1)
##(0.2,0.75) 사각형의 시작점 0.5 가로길이 0.2 세로길이를 뜻한다.
## alpha 색깔의 명도를 나타내준다 인수를 바꿔서 결과 변화를 확인해보자!
rect = plt.Rectangle((0.2, 0.75), 0.5, 0.2, color='k', alpha=0.3) 
#(0,7,0,2) 원의 중심 을 뜻한다 / 0.15 원의 반지름을 뜻한다.
circ = plt.Circle((0.7, 0.2), 0.15, color='b', alpha=0.3) 
#꼭지점의 좌표
pgon = plt.Polygon([[0.15, 0.15], [0.35, 0.4], [0.2, 0.6]],color='g', alpha=0.5)
## ax subplot에 도형을 추가한다.
ax.add_patch(rect) 
ax.add_patch(circ)
ax.add_patch(pgon)

# 막대그래프를 서브그래프를 이용하여 그리는 예
fig, axes = plt.subplots(2, 1)
data = Series(np.random.rand(16), index=list('abcdefghijklmnop'))



data.plot(kind='bar', ax=axes[0], color='k', alpha=0.9)
data.plot(kind='barh', ax=axes[1], color='k', alpha=0.7)

# 데이터프레임으로부터 막대그래프를 그리는 예
df = DataFrame(np.random.rand(6, 4),# 6 x 4 형태의 표준 정규분포
               index=['one', 'two', 'three', 'four', 'five', 'six'],
               columns=pd.Index(['A', 'B', 'C', 'D'], name='Genus'))

df
plt.plot(randn(30), 'ko--')

#클래스,상속 연습

class TV:
    
    def __init__(self):
        self.__size = '100 x 100'
        
    def getSize(self):
        return self.__size
        
class ColorTV(TV):
    
    def __init__(self,initValue):
        self.__resolution = initValue
        super().__init__()
        
    def getResolution(self):
        return self.__resolution
    
    def printResolution(self):
        print(f'사이즈:{self.getSize()} , 해상도: {self.__resolution}')
        
ctv = ColorTV("1000*700")

ctv.printResolution()
