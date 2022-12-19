data class Ticket(val companyName:String,val name: String, var date: String,var seatNumber:Int)
//toString(), hashCode(),equlas(),copy()
class TicketNormal(val companyName:String,val name: String, var date: String,var seatNumber:Int)


fun main(){
    val ticketA = Ticket("koreanAir","jaeyong","2022-12-19",15)
    val ticketB = TicketNormal("koreanAir","jaeyong","2022-12-19",15)

    println(ticketA)
    println(ticketB)
}
