#include <vector>

namespace helpers {
  
  struct AirportNode {
    AirportNode(std::string n)
      : name(n),
        unlockedDestinations(0)
    {}
    
    std::string name;
    std::unordered_map<std::string, AirportNode*> connections;
    int unlockedDestinations;
    std::unordered_set<std::string> unlockedDestinationsList;
  };
  
  void dfs( AirportNode*, std::unordered_set<string>&, std::unordered_set<string>& );
  void dfs( AirportNode*, AirportNode*, std::unordered_set<string>&, const std::unordered_set<string>& );
  bool updateUnreachableList( std::unordered_set<string>&, AirportNode* );
}

int airportConnections(vector<string> airports, vector<vector<string>> routes,
                       string startingAirport) {  
  // Iterate through list of airports and create map of nodes and initialize
  // the set of currently unreachable airports (all of them at the start)
  std::unordered_map<std::string, helpers::AirportNode*> airportGraph;
  std::unordered_set<string> unreachable;
  for( auto airport : airports ) {
    unreachable.insert(airport);
    airportGraph.insert({airport, new helpers::AirportNode(airport)});
  }
  
  // Iterate through routes list and set all of the connections of each node.
  for( auto route : routes ) {
    airportGraph[route[0]]->connections.insert({route[1], airportGraph[route[1]]});
  }
  
  // Perform depth-first-search on all airports connected to the starting airport.
  {
    std::unordered_set<string> visited;
    helpers::dfs( airportGraph[startingAirport], visited, unreachable );
  }
  
  // Determine all of the airports that each unreachable airport could unlock if there
  // was a route to it.
  for( auto airport : unreachable ) {
    std::unordered_set<string> visited;
    helpers::dfs(airportGraph[airport], airportGraph[airport], visited, unreachable);
  }
  
  // Create a vector of all of the unreachable nodes so it can be sorted based on the number
  // of airports each node can unlock.
  vector<helpers::AirportNode*> sortedUnreachable;
  for( auto airport : unreachable ) {
    sortedUnreachable.push_back(airportGraph[airport]);
  }
  std::sort(sortedUnreachable.begin(), sortedUnreachable.end(), [](helpers::AirportNode* a, helpers::AirportNode* b) {
    return a->unlockedDestinations > b->unlockedDestinations;
  });
  
  // Iterate through the sorted list of unreachable airports, updating the active list
  // of unreachable airports, and tallying the number of times airports were removed
  // from that list.
  int totalNewRoutes = 0;
  for( auto airport : sortedUnreachable ) {
    if( helpers::updateUnreachableList(unreachable, airport) ) {
      totalNewRoutes++;
    }
  }
  
  return totalNewRoutes;
}

/* Recursively searches through all connected nodes, removing any nodes found from the 
 * unreachable list.
**/
void helpers::dfs( AirportNode* node, std::unordered_set<string>& visited, std::unordered_set<string>& unreachable ) {
  // Any given branch of the search is over if we loop back to a node
  // that has already been visited.
  if( visited.find(node->name) != visited.end() )
    return;
  
  visited.insert(node->name);
  unreachable.erase(node->name);
  
  for( auto connection : node->connections ) {
    dfs(connection.second, visited, unreachable);
  }
}

/* Performs depth-first-search on the @originalNode, updating the list of nodes that the given
 * @originalNode can unlock.
**/
void helpers::dfs( AirportNode* originalNode, AirportNode* node, std::unordered_set<string>& visited, const std::unordered_set<string>& unreachable ) {
  // The search ends if we encounter a visited node since the search started, or a node that is not unreachable.
  if( visited.find(node->name) != visited.end() || unreachable.find(node->name) == unreachable.end() )
    return;
  
  originalNode->unlockedDestinations++;
  originalNode->unlockedDestinationsList.insert(node->name);
  visited.insert(node->name);
  
  for( auto connection : node->connections ) {
    dfs(originalNode, connection.second, visited, unreachable);
  }
}

/* Updates the @unreachable set by removing all nodes that the given @airport unlocks.
**/
bool helpers::updateUnreachableList( std::unordered_set<string>& unreachable, AirportNode* airport ) {
  bool updated = false;
  for( auto unlockedAirport : airport->unlockedDestinationsList ) {
    if( unreachable.find(unlockedAirport) != unreachable.end() ) {
      updated = true;
      unreachable.erase(unlockedAirport);
    }
  }
  return updated;
}


int main() {
  return 0;
}