#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  int size;
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    size = n;
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();

	for (int i = (int)(size/2)-1; i>=0; --i)
		SiftDown(i);
  }

  // SiftDown function to be utilized in MIN_heapBuild process
  void SiftDown(int id) {
  	int maxIndex = id;

	int l = 2*id + 1;  // left child index
	if ((l < size) && (data_[l] < data_[maxIndex]))
		maxIndex = l;
	
	int r = 2*id + 2;  // right child index
	if ((r < size) && (data_[r] < data_[maxIndex]))
		maxIndex = r;
  
  	if (id != maxIndex){
		swap(data_[id], data_[maxIndex]);
		//SiftDown(maxIndex);
		swaps_.push_back(make_pair(id, maxIndex));
		SiftDown(maxIndex);
	}
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
