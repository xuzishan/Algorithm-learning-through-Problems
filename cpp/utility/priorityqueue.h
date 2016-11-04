#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H
	#include <vector>
	#include <functional>
	using namespace std;
	template<typename T, typename Compare=less<T>>
	class PriorityQueue {
	private:
		vector<T> heap;
		int indexOfMost(int i);
		void siftDown(int index);
		void liftUp(int index);
	public:
		bool empty();
		int size();
		T top();
		void pop();
		void push(T x);
		int search(T &x);
		void replace(T x, int i);
	};
	template<typename T, typename Compare>
	int PriorityQueue<T, Compare>::indexOfMost(int i){
		int heapSize=size();
		int j=i;
		if (2*i+1<heapSize && Compare()(heap[i], heap[2*i+1]))
			j=2*i+1;
		if (2*(i+1)<heapSize && Compare()(heap[j], heap[2*(i+1)]))
			j=2*(i+1);
		return j;
	}
	template<typename T, typename Compare>
	void PriorityQueue<T, Compare>::siftDown(int index){
		int i=index, j=indexOfMost(index);
		while (i != j) {
			swap(heap[i], heap[j]);
			i=j;
			j=indexOfMost(i);
		}
	}
	template<typename T, typename Compare>
	void PriorityQueue<T, Compare>::liftUp(int index){
		int i=index;
		int j=(i%2)?(i-1)/2:(i/2);
		while (i>0 && Compare()(heap[j], heap[i])) {
			swap(heap[i], heap[j]);
			i=j;
			j=(i%2)?(i-1)/2:(i/2);
		}
	}
	template<typename T, typename Compare>
	bool PriorityQueue<T, Compare>::empty(){
		return heap.empty();
	}
	template<typename T, typename Compare>
	int PriorityQueue<T, Compare>::size(){
		return heap.size();
	}
	template<typename T, typename Compare>
	T PriorityQueue<T, Compare>::top() {
		return heap[0];
	}
	template<typename T, typename Compare>
	void PriorityQueue<T, Compare>::push(T x){
		int heapSize=size();
		heap.push_back(x);
		liftUp(heapSize);
	}
	template<typename T, typename Compare>
	void PriorityQueue<T, Compare>::pop(){
		if (!empty()) {
			int heapSize=size()-1;
			heap[0]=heap[heapSize];
			heap.erase(heap.end()-1);
			siftDown(0);
		}
	}
	template<typename T, typename Compare>
	int PriorityQueue<T, Compare>::search(T &x) {
		int n=size();
		for (int i=0; i<n; i++)
			if(heap[i]==x){
				x=heap[i];
				return i;
			}
			return -1;
	}
	template<typename T, typename Compare>
	void PriorityQueue<T, Compare>::replace(T x, int i){
		T y=heap[i];
		heap[i]=x;
		if (Compare()(y, x)){
			liftUp(i);
			return;
		}
		if (Compare()(x, y))
			siftDown(i);
	}
#endif /*_PRIORITYQUEUE_H*/