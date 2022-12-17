open class Human constructor(val name : String = "No name"){

    constructor(name : String,age :Int) : this(name){
        println("my name is ${name}, ${age} years old")
    }

    init{
        println("New human has been born!!")
    }

    fun eatingCake(){
        println("This is so Yammy~")
    }

    open fun singASong(){
        println("lalala")
    }

}

//상속
class Korean : Human(){

    override fun singASong(){
        super.singASong()
        println("라라라")
    }
}



fun main(){

    val human = Human("jaeyong")
    human.eatingCake()
    println(human.name)

    val human2 = Human()
    println(human2.name)

    val human3 = Human("jaeyong",23)
    human3.singASong()

    val korean = Korean()
    korean.singASong()
}

