#in the following functions I'm using shuffle to fill an array with random letters and then joining them to form a string.
def publisher
  ('a'..'z').to_a.shuffle[0, 8].join
end
def book_name
  ('a'..'z').to_a.shuffle[0, 8].join
end
def author_name
  first = ('a'..'z').to_a.shuffle[0, 8].join
  last = ('a'..'z').to_a.shuffle[0, 6].join
  "#{first} #{last}"#returning the string with a space between first and last name. 
end
#I'm generating a 12 digit number using rand
def isbn
  rand(10**11...10**12)
end

file_name = "books.txt"
File.open(file_name, "w") do |file|
  for i in 1..10000
    isbn_num = isbn()
    book = book_name()
    author = author_name()
    publish = publisher()
    #write these random names/numbers to the file in the correct format. 
    file.write("#{isbn_num},#{author},#{book},#{publish}\n")
  end
end

