fun main(){
    helloWorld()

    println(add(10,20))

    //String Template
    val name = "jaeyong"
    val lastName = "Park"
    println("my name is ${name + lastName} I'm 23")

    println("is this true? ${1==0}")

    checkNum(1)

    forAndWhile()

    nullcheck()
}

// 함수
fun helloWorld()  {
    println("Hello World!")
}

fun add(a : Int, b : Int) : Int{
    return a+b
}

//val var
//val = value 바꿀수 없는 값

fun hi(){
    val a : Int = 10
    var b : Int = 9

    var e : String

    val c = 100
    var d = 100

    var name = "jaeyong"
}

fun maxBy(a : Int, b : Int):Int{
    if(a>b){
        return a
    }else{
        return b
    }
}

fun maxBy2(a : Int, b : Int):Int = if(a>b) a else b

fun checkNum(score : Int){
    when(score){
        0 -> println("this is 0")
        1 -> println("this is 1")
        2,3 -> println("this is 2 or 3")
        else -> println("I don't know")
    }

    var b: Int = when(score){
        1-> 1
        2-> 2
        else -> 3
    }

    println("b : ${b}")

    when(score) {
        in 90..100 -> println("you are genius")
        in 10..8-90 -> println("not bad")
        else -> println("okay")
    }
}

//배열 리스트
fun array(){
    val array = arrayOf(1,2,3)
    val list = listOf(1,2,3)

    val array2 : Array<Any> = arrayOf(1,"d",3.4f)
    val lis2 = listOf(1,"d",11L)

    array[0] = 3
    var result = list.get(0)

    val arrayList = arrayListOf<Int>()
    arrayList.add(10)
    arrayList.add(20)
}

//반복문 for , while
fun forAndWhile(){
    val students = arrayListOf("jae","yong","park")

    for(name in students){
        println(name)
    }
    
    for((index,name) in students.withIndex()){
        println("${index+1}번째 학생: ${name}")
    }

    var sum = 0
    for(i in 1..10 step 2){
        sum+=i
    }
    println(sum)

    var index = 0
    while(index < 10){
        println("current index : ${index++}")
    }
}

//Nullable / NonNUll

fun nullcheck(){
    //NPE :NUll Pointer Exception

    var name = "jaeyong"

    var nullName : String? = null

    var nameInUpperCase : String = name.toUpperCase()

    var nullNameInUpperCase : String? = nullName?.toUpperCase()

    // ?:

    var lastName : String? = null

    var fullName = name+(lastName?: " No lastName")

    println(fullName)

    lastName = "Park"
    fullName = name+(lastName?: " No lastName")
    println(fullName)

    //!!
    ignoreNulls("a")
    try {
        ignoreNulls(null)
    }catch (e : NullPointerException){
        println("NPE")
    }


}

fun ignoreNulls(str : String?){
    val mNotNull : String = str!!
    val upper = mNotNull.toUpperCase()

    val email = "jaeyong36@naver.com"
    email?.let{
        println("my email is ${email}")
    }
}

