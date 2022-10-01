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
