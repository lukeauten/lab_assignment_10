#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie *createTrie();

// Trie structure
struct Trie
{	
    int isWord;
    struct Trie *next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *tempTrie = pTrie;
    int temp = 0, nextIndex;

    while(temp != strlen(word)){
        nextIndex = word[temp] - 'a';
        if(tempTrie->next[nextIndex] == NULL){
            tempTrie->next[nextIndex] = createTrie();
        }
        tempTrie = tempTrie->next[nextIndex];
        temp++;
    }
    tempTrie->isWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *tempTrie = pTrie;
    int temp = 0, nextIndex;

    while(temp != strlen(word)){
        nextIndex = word[temp] - 'a';
        if(tempTrie->next[nextIndex] == NULL){
            return 0;
        }
        tempTrie = tempTrie->next[nextIndex];
        temp++;
    }
    return tempTrie->isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++){
        if(pTrie->next[i] != NULL){
            deallocateTrie(pTrie->next);
        }
    }
    free(pTrie);
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *tempTrie = (struct Trie*)malloc(sizeof(struct Trie));
    tempTrie->isWord = 0;

    for(int i = 0; i < 26; i++){
        tempTrie->next[i] = NULL;
    }

    return tempTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    int wordCount = 0;
    char *tempString = (char*)malloc(sizeof(char) * 50);

    fgets(tempString, 50, fp);
    sscanf(tempString, "%d", &wordCount);

    for(int i = 0; i < wordCount; i++){
        fgets(tempString, 50, fp);
        sscanf(tempString, "%s", pInWords[i]);
    }
    return wordCount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}