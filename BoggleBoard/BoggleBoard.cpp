#include <vector>

using namespace std;


namespace helpers {
  
  struct TrieNode {
      unordered_map<char, TrieNode*> childNodes;
      TrieNode* prevNode;
  };
  
  struct Trie {
    Trie();
    void addWord(string word);
    
    TrieNode* root;
    TrieNode* currentNode;
    char endSymbol;
  };
  
  void traverseBoard( int i, 
                      int j, 
                      vector<vector<char>>& board, 
                      Trie& wordTrie,
                      vector<vector<bool>>& visited,
                      unordered_set<string>& result,
                      string currentString = "" )
  {
    if( !visited[j][i] ) {
      visited[j][i] = true;
      char currentChar = board[j][i];
      
      // Check if the current character on the board is a match for a valid word.
      if( wordTrie.currentNode->childNodes.find(currentChar) == wordTrie.currentNode->childNodes.end() ) {
        // Mark this square as unvisited as the stack unwinds. The visitation
        // criterion only applies while the stack is winding.
        visited[j][i] = false;
        return;
      }
      
      currentString.push_back(currentChar);
      TrieNode* childNode = wordTrie.currentNode->childNodes[currentChar];
      wordTrie.currentNode = childNode; // Move to the next node.
      
      // Push the current string into the result array if we have reached an end point in the trie.
      if( wordTrie.currentNode->childNodes.find(wordTrie.endSymbol) != wordTrie.currentNode->childNodes.end() ) {
        result.insert(currentString);
      }
      
      // Recursively check all neighboring squares for a possible continuation
      // of a valid word.
      int boardHeight = board.size();
      int boardWidth = board[0].size();     
      if( i < boardWidth - 1 ) { // right
        traverseBoard(i + 1, j, board, wordTrie, visited, result, currentString);
      }
      if( i < boardWidth - 1 && j > 0 ) { // up/right
        traverseBoard(i + 1, j - 1, board, wordTrie, visited, result, currentString);
      }
      if( i < boardWidth - 1 && j < boardHeight - 1 ) { // down/right
        traverseBoard(i + 1, j + 1, board, wordTrie, visited, result, currentString);
      }
      if( i > 0 ) { // left
        traverseBoard(i - 1, j, board, wordTrie, visited, result, currentString);
      }
      if( i > 0 && j > 0 ) { // up/left
        traverseBoard(i - 1, j - 1, board, wordTrie, visited, result, currentString);
      }
      if( i > 0 && j < boardHeight - 1 ) { // down/left
        traverseBoard(i - 1, j + 1, board, wordTrie, visited, result, currentString);
      }
      if( j > 0 ) { // up
        traverseBoard(i, j - 1, board, wordTrie, visited, result, currentString);
      }
      if( j < boardHeight - 1 ) { // down
        traverseBoard(i, j + 1, board, wordTrie, visited, result, currentString);
      }
      // Mark this square as unvisited as the stack unwinds. The visitation
      // criterion only applies while the stack is winding.
      visited[j][i] = false;
      // Unwind the current location in the trie as the stack is unwound.
      wordTrie.currentNode = wordTrie.currentNode->prevNode;
    }
  }
  
}

/* 
 * This is the main entry point of the algorithm.
**/
vector<string> boggleBoard(vector<vector<char>> board, vector<string> words) {
  int boardHeight = board.size();
  int boardWidth = board[0].size();
  helpers::Trie wordTrie;
  unordered_set<string> result;
  
  // Store the list of valid words in a trie structure
  // for efficient access while traversing the board.
  for( auto word : words ) {
    wordTrie.addWord(word);
  }
  
  // Iterate through each square on the board, performing
  // DFS recursively whenever characters of a valid word are found.
  for( int j = 0; j < boardHeight; j++ ) {
    for( int i = 0; i < boardWidth; i++ ) {
      vector<vector<bool>> visited(boardHeight, vector<bool>(boardWidth, false));
      wordTrie.currentNode = wordTrie.root; // This is a new search branch so reset the wordTrie
      helpers::traverseBoard(i, j, board, wordTrie, visited, result);
    }
  }
  
  // Toss the resulting set into an array
  // to conform to the output criterion.
  vector<string> resultArray;
  for( auto word : result ) {
    resultArray.push_back(word);
  }
  return resultArray;
}

helpers::Trie::Trie()
  : root(new TrieNode),
    currentNode(root),
    endSymbol('*') { }

void helpers::Trie::addWord(string word) {
  TrieNode* currentNode = root;
  for( auto character : word ) {
    if( currentNode->childNodes.find(character) == currentNode->childNodes.end() ) {
      currentNode->childNodes.insert({character, new TrieNode});
    }
    currentNode->childNodes[character]->prevNode = currentNode;
    currentNode = currentNode->childNodes[character];
  }
  currentNode->childNodes.insert({endSymbol, nullptr});
}


int main() {
  return 0;
}