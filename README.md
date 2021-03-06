# DictionarySearch-using-Trie
this is a data structure and algorithm project which is made using TRIE data structure to help our user to find the meaning, synonyms, antonyms and examples of an entered word and if the user enters an invalid word then we help them to explore more words similar to the entered word. 
What makes the trie structure really perform well in these situations is that the cost of looking up a word or prefix is fixed and dependent only on the number of characters in the word and not on the size of the vocabulary.
However, despite this, even a compressed trie will usually require more memory than a tree or array. This is because, for each node, at least 26 x sizeof(pointer) bytes are necessary, plus some overhead for the object and additional attributes. On a 64-bit machine, each node requires more than 200 bytes, whereas a string character requires a single byte, or two if we consider UTF strings.
Key Features :

    Insert, search and delete words in the dictionary.
    Alphabetically printing the words.
    Prefix searching i.e. all words with the entered prefix will be displayed.
    Nearest neighbor search i.e. shows suggested words if the word you are looking for is not found.

