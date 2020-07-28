using namespace std;

class OrgChart {
public:
  char name;
  vector<OrgChart *> directReports;

  OrgChart(char name) {
    this->name = name;
    this->directReports = {};
  }

  void addDirectReports(vector<OrgChart *> directReports);
};

int recurse(OrgChart* manager,
             OrgChart* reportOne,
             OrgChart* reportTwo,
             OrgChart*& result) {
  // For the current manager, determine how many direct reports
  // are reports of interest (either reportOne or reportTwo)
  int numReports = 0;
  if( manager->name == reportOne->name )
    numReports++;
  if( manager->name == reportTwo->name )
    numReports++;
  
  // Perform DFS on hierarchy of reports.
  for( auto r : manager->directReports ) {
    // No reports for a 'manager' means just return 0.
    if( r == nullptr )
      return 0;
    // As the recursion unwinds, continue to sum all of the 'hits' for
    // reports of interest.
    numReports = numReports + recurse(r, reportOne, reportTwo, result);
  }
  
  // Set the result ptr equal to the current manager if we reached
  // the convergence point for having both reports of interest.
  // Once the result ptr is set, we do not want to set it again
  // (this would be a possibility for manager further up the hierarchy,
  // which we do not want).
  if( numReports == 2 && result == nullptr ) {
    result = manager;
  }
    
  return numReports;
}

OrgChart *getLowestCommonManager(OrgChart *topManager, OrgChart *reportOne,
                                 OrgChart *reportTwo) {
  OrgChart* result = nullptr;
  recurse(topManager, reportOne, reportTwo, result);
  return result;
}


int main() {
  return 0;
}