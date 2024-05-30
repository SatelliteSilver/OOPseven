#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <Windows.h>
using namespace std;

class Queue {
	public:
		Queue() { NI = 0; NO = 0; capacity = 0; }
		~Queue() {}
		Queue(int NI, int NO, int cap) {
			this->NI = NI;
			this->NO = NO;
			this->capacity = cap;
		}

		int NI, NO, capacity;
		
		float anal_fullness(int packetNum) {
			return float(packetNum) / float(capacity);
		}
		float anal_lossrate(int loss, int totalPacket) {
			return float(loss) / float(totalPacket);
		}
		void enqueue(int* ni, vector<int> &queue, int* loss) {
			*ni = rand() % NI;
			for (int i = 0; i < *ni; i++) {
				if (queue.size() < capacity)
					queue.push_back(rand() % 20);
				if (queue.size() >= capacity)
					*loss += 1;
			}
		}
		void dequeue(int* no, vector<int>& queue) {
			if (queue.size() != 0) {
				*no = rand() % NO;
				for (int i = 0; i < *no; i++) {
					queue.erase(queue.begin());
					if (queue.size() == 0) break;
				}
			}
		}
		void addNO() {
			NO += 1;
		}
};

int main() {
	// init
	srand(time(0));
	ofstream anal, compare;
	compare.open("analog.txt");
	int ni, no;
	int sampleNum = 20;
	Queue test(50, 50, 100);
	vector <int> q;
	int loss[20], totalPacket = 0, timeLimit = 1000, maximumPacket = 0, sample = 20;
	float totalFullness = 0;
	int NumPacket[1000][20];
	int elapsedSeconds = 0, T = 1;
	for (int i = 0; i < sample; i++) {
		loss[i] = 0;
	}
	
	// Queueing
	for (int i = 0; i < sample; i++) {
		test.addNO();
		q.clear();
		elapsedSeconds = 0;
		while (elapsedSeconds < timeLimit) {
			elapsedSeconds += T;
			test.enqueue(&ni, q, &loss[i]);
			NumPacket[elapsedSeconds - 1][i] = q.size();
			test.dequeue(&ni, q);
		}
	}
	
	// Analysis
	cout << endl;
	for (int j = 0; j < sample; j++){
		for (int i = 0; i < timeLimit; i++) {
			if (anal.is_open())
				anal << NumPacket[i] << endl;
			if (maximumPacket < NumPacket[i][j])
				maximumPacket = NumPacket[i][j];
			totalPacket += NumPacket[i][j];
			totalFullness+=test.anal_fullness(NumPacket[i][j]);
		}
		compare << j + 51 << "\t" << totalFullness / timeLimit << "\t" << float(loss[j]) / float(totalPacket)<< "\n";
		cout << "Queue Fullness: " << totalFullness/timeLimit << endl;
		cout << "Packet Loss Rate: " << float(loss[j]) / float(totalPacket) << endl;
		cout << "최대 패킷 개수: " << maximumPacket << endl;
		cout << "평균 패킷 개수: " << totalPacket / timeLimit << endl;
		cout << "손실된 패킷 개수: " << loss[j] << endl;
		maximumPacket = 0;
		totalPacket = 0;
		totalFullness = 0;
	}
	
	compare.close();
	return 123;
}
