#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <Windows.h>
using namespace std;

int main() {
	// init
	srand(time(0));
	ofstream anal;
	anal.open("queue.txt");
	int NI = 50, NO = 70, ni, no;
	vector <int> q;
	int capacity = 100, lost = 0, totalPacket=0, timeLimit=120, maximumPacket=0;
	int NumPacket[120];
	int elapsedSeconds = 0, T = 1;

	// Analysis
	while (elapsedSeconds < timeLimit) {
		Sleep(T * 1000);  // milliseconds
		elapsedSeconds += T;
		cout << "  Elapsed time[sec] = " << elapsedSeconds << "   " << endl;

		// enqueue
		ni = rand() % NI;
		for (int i = 0; i < ni; i++) {
			if (q.size() < capacity)
				q.push_back(rand() % 20);
			if (q.size() >= capacity)
				lost++;
		}
		if(maximumPacket<q.size())
			maximumPacket = q.size();
		totalPacket += q.size();
		cout << "queue에 저장된 패킷의 개수: " << q.size() << endl;
		NumPacket[elapsedSeconds-1] = q.size();

		// dequeue
		if (q.size() == 0) {
			cout << " empty queue\n";
		}
		else {
			no = rand() % NO;
			for (int i = 0; i < no; i++) {
				q.erase(q.begin());
				if (q.size() == 0) break;
			}
		}
		cout << endl;
	}
	
	cout << endl;
	for(int i = 0; i < timeLimit; i++) 
		if(anal.is_open())
		anal << NumPacket[i] << endl;
	cout << "최대 패킷 개수: " << maximumPacket << endl;
	cout << "평균 패킷 개수: " << totalPacket / timeLimit << endl;
	cout << "손실된 패킷 개수: " << lost << endl;
	anal.close();
	
	return 123;
}
