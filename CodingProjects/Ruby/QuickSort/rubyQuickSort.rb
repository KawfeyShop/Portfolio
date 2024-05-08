def getISBN(line)
  #using regex to get the ISBN
  pattern = /\d+/ #matching only numbers
  if match = line =~ pattern
    isbnNumbers= $&#including the entire matching string
  else
    puts "there was an error."
  end
  isbnNumbers.to_i
end

def getBook(line)
  #splitting the line by the commas
  words = line.split(",")
  #bookTitle is indexed at the 3rd spot in the array.
  bookTitle = words[2]
end

#to print in ascending order
def partition(pivot, isbnNum)
  #partition function that compares the pivot to the array and then assigns the number to the correct array.
  lowArray, highArray = [], []
  for i in 0...isbnNum.length do
    if isbnNum[i] < pivot
      lowArray << isbnNum[i]
    elsif isbnNum[i] > pivot
      highArray << isbnNum[i]
    end
  end
  return lowArray, highArray
end

#to print in reverse order
def oppositePartition(pivot, isbnNum)
  #partition function that compares the pivot to the array and then assigns the number to the correct array.
  lowArray, highArray = [], []
  for i in 0...isbnNum.length do
    if isbnNum[i] < pivot
      highArray << isbnNum[i]
    elsif isbnNum[i] > pivot
      lowArray << isbnNum[i]
    end
  end
  return lowArray, highArray
end

def pivot(array)
  #set the first number of the array as a pivot
  array[0]
end

#usage 1 and 3 quicksort
def u1u3quickSort(isbnNum)
  #keep going until the length of the array indicates that it's sorted.
  return isbnNum if isbnNum.length <= 1
  #set pivot
  pivotNum = pivot(isbnNum)
  #partition the array
  lowArray, highArray = partition(pivotNum, isbnNum[1..-1])
  #return the array including the pivot.
  return u1u3quickSort(lowArray) + [pivotNum] + u1u3quickSort(highArray)
end

#usage 2 quicksort
def u2quickSort(isbnNum)
  #keep going until the length of the array indicates that it's sorted. 
  return isbnNum if isbnNum.length <= 1
  #set pivot
  pivotNum = pivot(isbnNum)
  #partition the array
  lowArray, highArray = oppositePartition(pivotNum, isbnNum[1..-1])
  #return the array including the pivot. 
  return u2quickSort(lowArray) + [pivotNum] + u2quickSort(highArray)
end

isbnNumbers = [] #isbn auxillary array
bookNames = [] #bookName auxillary array

File.foreach("books.txt") do |lines|
  isbnNumber = getISBN(lines)
  isbnNumbers << isbnNumber#appending the array.
  bookName = getBook(lines)
  bookNames << bookName
end

usage1 = u1u3quickSort(isbnNumbers)
usage2 = u2quickSort(isbnNumbers)
usage3 = u1u3quickSort(bookNames)

#creating and outputting usage 1,2, and 3 in that order to a file named taskBOutput.txt
file_name = "taskBOutput.txt"
File.open(file_name, "w") do |file|
  usage1.each do |item|
    file.puts(item)
  end
  usage2.each do |item|
    file.puts(item)
  end
  usage3.each do |item|
    file.puts(item)
  end
end
