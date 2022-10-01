#별찍기
for i in range(10):
    print('*'*(i+1))
    
#가격 출력
price = int(input('볼펜 가격: '))
sale = int(input('볼펜 할인률(%): '))
cnt = int(input('볼펜 개수: '))
sol = int((price*cnt)*((100-sale)/100))
print(sol,"원",sep="")

#한번에 여러 개의 데이터 입력 받기
a, b = input('문자열 입력 : ').split()
print(a)
print(b)
a, b = input('문자열 입력 : ').split(',')
print(a)
print(b)

#한꺼번에 입력 받은 데이터의 탑입 변환
a,b = map(int,input('덧셈에 사용될 두 개의 정수를 입력 : ').split('/'))
print(a+b)

#출력
print("aaa","bbb,sep="",end="")
      
"""
아래 소스와 같이 year 리스트에 연도, population 리스트에 서울시 인구수가 저장되어 있는 상태에서 코드를 완성하여
실행결과와 같이 최근 3년간 연도와 인구수가 리스트로 출력되도록 하시오.
"""
year = [2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019]
population = [10249679, 10195318, 10143645, 10103233, 10022181, 9930616, 9857426, 9838892]
print(year[-3:])
print(population[-3:])

"""
다음 소스 코드를 완성하여 튜플 n에서 인덱스가 홀수인 요소들이 출력되도록 작성하시오.
"""
n = -32, 75, 97, -10, 9, 32, 4, -15, 0, 76, 14, 2
print(n[1::2])
      
"""
표준 입력으로 숫자 또는 문자열 여러 개가 입력되어 리스트 x에 저장되도록 하고 리스트 x의 마지막 요소 5개를 삭제한
뒤 튜플로 출력되도록 완성하시오.
"""
x = input().split()
del(x[-5:])
print(x)
      
"""
표준 입력으로 문자열 두 개가 각 줄에 입력되고 첫번째 문자열의 인덴스 번호가 홀수인 문자와 두번째 문자열에서 인덱
스가 짝수인 문자열을 연결하여 출력하는 프로그램을 작성하시오.
"""
a = input("#입력\n")
b = input()
sol = a[1::2]+b[::2]
print(sol)
      
#다음 소스 코드를 완성하여 게임 캐릭터의 체력(health)과 이동 속도(movement speed)가 출력되게 만드세요.
#딕셔너리
camille = {
'health': 575.6,
'health_regen': 1.7,
'mana': 338.8,
'mana_regen': 1.63,
'melee': 125,
'attack_damage': 60,
'attack_speed': 0.625,
'armor': 26,
'magic_resistance': 32.1,
'movement_speed': 340
}
print(camille['health'])
print(camille['movement_speed'])
      
#윤년 확인
year = int(input())
sol = "윤년X"
if year%4==0 and year%100!= 0 or year%400==0:
    sol ="윤년"
print(sol)
