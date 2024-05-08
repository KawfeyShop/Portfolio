import System.IO
import Data.List

-- Function to get the ISBN. This uses pattern matching and returns 1 thing from a line that contains a number 0-9
getISBN :: String -> Integer
getISBN line = read $ head $ wordsWhen (not . isDigit) line
    where isDigit c = c `elem` ['0'..'9']

-- Function used to split a string by comma. Used specifically to get the title using the format ISBN, author, title, publisher. This will grab the third parameter title. 
getBook :: String -> String
getBook line = case parts of
    (_:_:book:_) -> book --This is the line that gets the third parameter called book
    _ -> ""
    where  --This is where it splits the parameters by commas. 
        parts = split ',' line
        split :: Char -> String -> [String]
        split _ [] = [""]
        split delim (c:cs)
            | c == delim = "" : rest
            | otherwise = (c : head rest) : tail rest
            where
                rest = split delim cs

-- Quick sort for  ascending order
quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = quicksort smaller ++ [x] ++ quicksort larger --using recursion
    where
        smaller = filter (< x) xs --using the method we went over in class to fuel the recursion
        larger = filter (>= x) xs

-- Quick sort for descending order
quicksortDesc :: Ord a => [a] -> [a]
quicksortDesc [] = []
quicksortDesc (x:xs) = quicksortDesc larger ++ [x] ++ quicksortDesc smaller --same as above
    where
        smaller = filter (< x) xs
        larger = filter (>= x) xs

-- Equivalent to int main() {}. This is just using the functions above to sort and then write to the file. 
main :: IO ()
main = do
    contents <- readFile "books.txt" -- Reading from our books.txt.
    let ls = lines contents
        isbnNumbers = map getISBN ls
        bookNames = map getBook ls
        usage1 = quicksort (map show isbnNumbers)
        usage2 = quicksortDesc (map show isbnNumbers)
        usage3 = quicksort bookNames
        output = unlines (map show usage1 ++ map show usage2 ++ map show usage3)
--In case you want to test each usage individually: output = unlines (map show usage1)
    writeFile "taskBOutput.txt" output

-- This just helps with custom parsing.
wordsWhen :: (Char -> Bool) -> String -> [String]
wordsWhen p s = case dropWhile p s of
    "" -> []
    s' -> w : wordsWhen p s''
        where (w, s'') = break p s'
