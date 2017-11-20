#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

// using namespace std;




// DEFINITION OF AN OBJECT WORKER and OVERLOADING the compare operations
struct Worker{

	// Data
	int workerID;
	long long nextAvailableTime;
	
	// Initialization
	Worker(int ID = 0, long long time = 0):workerID(ID),nextAvailableTime(time){};

	// Overload Compare operations: These are friend functions!
	// They do not belong to the struct/class of Worker but they have access
	// to the private and protected members of the class
	friend bool operator<(const Worker worker1, const Worker worker2);
	friend bool operator>(const Worker worker1, const Worker worker2);
	friend bool operator==(const Worker worker1, const Worker worker2);
	friend bool operator!=(const Worker worker1, const Worker worker2);

	// Destructor
	~Worker(){};
};






// BINARY HEAP for WORKERS
class BinaryWorkerHeap{
	
	public:

		// Data
		int size_;
		vector<Worker> workers_;

		// Initialization (VECTOR PASS BY REFFERENCE)
		BinaryWorkerHeap(int size, vector<Worker>& workerArray):size_(size),workers_(workerArray){};

		
		// Heapify
		void WorkerHeapify(){
			for(int i = (int)(size_/2)-1; i >= 0; --i)
				WorkerSiftDown(i);
		}


		// Get the next available Worker
		Worker GetNext(){
			return workers_[0];
		}


		// Change the NextAvailableTime of a worker
		void ChangeWorkerAvailability(int id, long long time){
			
			long long previousTime = workers_[id].nextAvailableTime;
			workers_[id].nextAvailableTime = time;
			
			cout << workers_[id].workerID << "   " <<  workers_[id].nextAvailableTime << "\n";

			if (time > previousTime)
				WorkerSiftDown(id);
			else
				WorkerSiftUp(id);
		}


		// Destructor
		~BinaryWorkerHeap(){};


	private:

		void WorkerSiftDown(int id){
			int maxIndex = id;
			//cout << id << "\n";

			int l = 2*id + 1;  // left child index
			if ((l < size_) && (workers_[l] < workers_[maxIndex]))
				maxIndex = l;
						
			int r = 2*id + 2;  // right child index
			if ((r < size_) && (workers_[r] < workers_[maxIndex]))
				maxIndex = r;
							  
		  	if (id != maxIndex){
				swap(workers_[id], workers_[maxIndex]);
				WorkerSiftDown(maxIndex);
			}
		}

		void WorkerSiftUp(int id){
			int i = id;
			while ( (i > 0) && (workers_[(int)(i-1)/2] > workers_[i]) ){
				swap(workers_[(int)(i-1)/2],workers_[i]);
				i = (int)((i-1)/2);
			}
		}
};







// THE CLASS THAT BELONGS TO HOMEWORK
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;


  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }


  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }


  void AssignJobs() {
    
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);

	// initialize the array of workers
    vector<Worker> workers(num_workers_);
    for(int i = 0; i < num_workers_; ++i)
    	workers[i] = Worker(i,0.0);

	// heapify the workers vector
	BinaryWorkerHeap workersQueue(num_workers_, workers);
	workersQueue.WorkerHeapify(); // This is unneccessary after initialization but it is a good practice to do it.
    
    for (int i = 0; i<jobs_.size(); ++i){
		int durationOfCurrentJob = jobs_[i];
		Worker availableWorker = workersQueue.GetNext();
		assigned_workers_[i] = availableWorker.workerID;
		start_times_[i] = next_free_time[availableWorker.workerID];
		next_free_time[availableWorker.workerID] = availableWorker.nextAvailableTime + durationOfCurrentJob;
		workersQueue.ChangeWorkerAvailability(availableWorker.workerID, (availableWorker.nextAvailableTime + durationOfCurrentJob));

		//cout << availableWorker.nextAvailableTime << "\n";
	}

    //// TODO: replace this code with a faster algorithm.
    //assigned_workers_.resize(jobs_.size());
    //start_times_.resize(jobs_.size());
    //vector<long long> next_free_time(num_workers_, 0);
    //for (int i = 0; i < jobs_.size(); ++i) {
    //  int duration = jobs_[i];
    //  int next_worker = 0;
    //  for (int j = 0; j < num_workers_; ++j) {
    //    if (next_free_time[j] < next_free_time[next_worker])
    //      next_worker = j;
    //  }
    //  assigned_workers_[i] = next_worker;
    //  start_times_[i] = next_free_time[next_worker];
    //  next_free_time[next_worker] += duration;
    //}
  }


 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}




bool operator<(Worker worker1, Worker worker2){
	if (worker1.nextAvailableTime == worker2.nextAvailableTime)
		return worker1.workerID < worker2.workerID;
	return worker1.nextAvailableTime < worker2.nextAvailableTime;
}

bool operator>(Worker worker1, Worker worker2){
	if (worker1.nextAvailableTime == worker2.nextAvailableTime)
		return worker1.workerID > worker2.workerID;
	return worker1.nextAvailableTime > worker2.nextAvailableTime;
}

bool operator==(Worker worker1, Worker worker2){
	return (worker1.nextAvailableTime == worker2.nextAvailableTime);
}

bool operator!=(Worker worker1, Worker worker2){
	return (worker1.nextAvailableTime != worker2.nextAvailableTime);
}
