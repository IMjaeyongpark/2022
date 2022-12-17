fun main(){
    helloWorld()

    println(add(10,20))

    //String Template
    val name = "jaeyong"
    val lastName = "Park"
    println("my name is ${name + lastName} I'm 23")

    println("is this true? ${1==0}")
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
