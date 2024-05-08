import scala.io.Source

//returning a long since the ISBN's are longer than allowed for int in scala
def getISBN(line: String): Long = {
  //regex to find the numbers of the isbn 
  val digits = "\\d+".r.findFirstIn(line).getOrElse("0")
  //returns 0L if it's not a valid string of ints
  if (digits.matches("\\d+")) digits.toLong else 0L
}

//getting second index which is the bookname.
def getBook(line: String): String = line.split(",")(2)

//returning the numbers that are less than the pivot. 
def partition(pivot: Long, isbnNum: List[Long]): (List[Long], List[Long]) =
  isbnNum.partition(_ < pivot)
//returning the numbers that are more than the pivot. 
def oppositePartition(pivot: Long, isbnNum: List[Long]): (List[Long], List[Long]) =
  isbnNum.partition(_ > pivot)
//Returning the first number(head) as an option, if not OL
def pivot(array: List[Long]): Long = array.headOption.getOrElse(0L)

//In the following, these contain the recursive calls to return the sorted list for each usage.
//Will only be documenting this first one since all of them are essentially the same. Will do for some exceptions.  
def u1quicksort(isbnNum: List[Long]): List[Long] =
  if (isbnNum.length <= 1) isbnNum
  else {
    val pivotNum = pivot(isbnNum)
    //return a high and low array after partitioning it 
    val (lowArray, highArray) = partition(pivotNum, isbnNum.tail)
    //returning in the format of lowarray, pivot, higharray. 
    u1quicksort(lowArray) ::: List(pivotNum) ::: u1quicksort(highArray)
  }

def u3quicksort(bookNames: List[String]): List[String] =
  if (bookNames.length <= 1) bookNames
  else {
    val pivotName = bookNames.head
    //x => x < pivotName returns a low array otherwise returns to high array. 
    //uses tail to exclude the head since it is the pivot. 
    val (lowArray, highArray) = bookNames.tail.partition(_ < pivotName)
    u3quicksort(lowArray) ::: List(pivotName) ::: u3quicksort(highArray)
  }

def u2quicksort(isbnNum: List[Long]): List[Long] =
  if (isbnNum.length <= 1) isbnNum
  else {
    val pivotNum = pivot(isbnNum)
    val (lowArray, highArray) = oppositePartition(pivotNum, isbnNum.tail)
    u2quicksort(lowArray) ::: List(pivotNum) ::: u2quicksort(highArray)
  }

//reading from the books.txt and then creates a tuple of lists to fill 
val (isbnNumbers, bookNames) = Source.fromFile("books.txt").getLines().foldLeft((List.empty[Long], List.empty[String])) {
    //uses the get... functions to populate the isbnNumber and bookName and then uses the :+ to append the lists
    //when you find these in a line then do this... This makes sure that it doesn't populate the 0L above. 
    case ((isbnAcc, bookAcc), line) =>
    val isbnNumber = getISBN(line)
    val bookName = getBook(line)
    (isbnAcc :+ isbnNumber, bookAcc :+ bookName)
}
//assigning the usages to this 
val usage1 = u1quicksort(isbnNumbers)
val usage2 = u2quicksort(isbnNumbers)
val usage3 = u3quicksort(bookNames)
//writing to file and then closing it
val file_name = "taskBOutput.txt"
val writer = new java.io.PrintWriter(file_name)
try {
  usage1.foreach(writer.println)
  usage2.foreach(writer.println)
  usage3.foreach(writer.println)
} finally {
  writer.close()
}
