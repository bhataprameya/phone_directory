# phone_directory


Program creates a new phone directory by reading from a text file. In the text file, the name and phone number of a person should be separated by a comma, and there should be only one pair of a name and phone number per line. 

Once a phone directory is created as described above, all entries are sorted and displayed in alphabetical order of the First name. If multiple persons in the directory have the same First name, sort is done based on their Last name. If they have the same first and last name, sort is done based on their phone number. Randomized quicksort algorithm is used to do this.

After displaying the sorted phone directory, search for a given name, e.g., Bob Smith. If found, return its location in the directory. Otherwise, return “Name not found” message and return. Binary search algorithm is used to do this. 

“​void delete(char* name)​” function that searches for the name passed as the parameter, and delete the name and phone number found by search. If not found, prints an appropriate error message and return.

 “​void insert(char* name, char* phone_number)​” is used to insert a new pair of a name and phone number to the directory, keeping the directory sorted.
