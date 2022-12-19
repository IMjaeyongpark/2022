//람다
val square: (Int) -> (Int) = { number -> number * number }

val nameAge = { name: String, age: Int ->
    "my name is ${name} I'm ${age}"
}

fun main() {
    println(square(12))
    println(nameAge("jaeyong",23))

    val a = "jaeyong said"
    val b = "zz said"
    println(a.pizzaIsGreat())
    println(b.pizzaIsGreat())

    println(extendString("jaeyong",23))

    println(calculateGrade(97))

    val lamda = {number:Double->
        number == 4.3213
    }
    val lamda2 = {number:Double->
        number == 5.2343
    }

    println(invokeLamda(lamda))
    println(invokeLamda(lamda2))
    println(invokeLamda {it>3.22 })
    //마지막 파라미터 람다일때,하나 람다 가리킬때
    println(invokeLamda(){it>3.22})


}

//확장함수

val pizzaIsGreat : String.()->String = {
    this + "Pizza is the best!"
}

fun extendString(name:String, age :Int):String{

    val introduceMyself : String.(Int) ->String = {"I am ${this} and ${it} years old"}
    return name.introduceMyself(23)
}

//람다의 return

val calculateGrade : (Int) -> String = {
    when(it){
        in 0..40 -> "fail"
        in 41..70->"pass"
        in 71..100->"perfect"
        else -> "Error"
    }
}

fun invokeLamda(lamda : (Double)->Boolean) : Boolean{
    return lamda(5.2343)
}
