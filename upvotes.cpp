#include <iostream>

using namespace std;

// n any
// returns n choose 2
unsigned long long n_choose_2(int n) {
	if (n < 2) return 0L;
	if (n == 2) return 1L;
	unsigned long long long_n = n;
	return long_n * (long_n-1L) / 2L;
}

// n >= 2
// returns n choose 2 - (n-1) choose 2
unsigned long long n_diff(int n) {
	return n_choose_2(n) - n_choose_2(n-1);
}

class ReducedSequence {

private:
	unsigned int* seq;
	unsigned int start,
				 end,
				 size,
				 size_max;
	unsigned long long sum;

	void increment_start();
	void increment_end();
	void decrement_front();

public:
	ReducedSequence(int);
	~ReducedSequence();

	unsigned long long get_sum() { return sum; }

	void increment_curr(bool);
	void increment_new(bool);

	void print_seq();

};

void ReducedSequence::increment_start() {
	start++;
	if (start == size_max) {
		start = 0;
	}
}

void ReducedSequence::increment_end() {
	end++;
	if (end == size_max) {
		end = 0;
	}
}

ReducedSequence::ReducedSequence(int k) {
	seq = new unsigned int[k];
	seq[0] = 1;
	start = 0;
	end = 0;
	size = 1;
	size_max = k;
	sum = 0L;
}

ReducedSequence::~ReducedSequence() {
	delete[] seq;
}

void ReducedSequence::decrement_front() {
	if (seq[start] == 1) {
		increment_start();
		size--;
	} else {
		sum -= n_diff(seq[start]);
		seq[start]--;
	}
}

void ReducedSequence::increment_curr(bool first_k) {

	// front
	if (not first_k) {
		decrement_front();
	}

	// back
	seq[end]++;
	sum += n_diff(seq[end]);

}

void ReducedSequence::increment_new(bool first_k) {

	// front
	if (not first_k) {
		decrement_front();
	}

	// back
	increment_end();
	size++;
	seq[end] = 1;

}

void ReducedSequence::print_seq() {

	for (int i = 0; i < size; i++) {
		if ((start+i) < size_max) {
			cout << seq[start+i];
		} else {
			cout << start+i-size_max;
		}
		cout << " ";
	}
	cout << endl;

	cout << "size: " << size << endl;
	cout << "sum: " << sum << endl;
}

/** This is a solution that uses very little 
	memory and computation to solve the problem. 
	It runs in O(N) time.
	In fact, this can be easily modified to 
	take data from a stream, and still achieve
	the same efficiency.
**/

int main () {

	int n, 
		k;
	cin >> n >> k;

	// grouped seq
	ReducedSequence non_neg(k);
	ReducedSequence non_pos(k);

	// counters
	int previous_number,
		current_number,
		numbers_read = 0;


	// read first number
	cin >> previous_number;
	numbers_read++;

	// edge case
	if (k == 1) cout << 0 << endl;

	for (; numbers_read < n; ) {
		cin >> current_number;
		numbers_read++;
		// cout << "Read number " << numbers_read << ": " << current_number << endl;

		bool first_k = numbers_read <= k;

		if (current_number > previous_number) {
			non_neg.increment_curr(first_k);
			non_pos.increment_new(first_k);
		} else if (current_number == previous_number) {
			non_neg.increment_curr(first_k);
			non_pos.increment_curr(first_k);
		} else {
			non_neg.increment_new(first_k);
			non_pos.increment_curr(first_k);
		}

		// cout << "-- debug" << endl;
		// non_neg.print_seq();
		// non_pos.print_seq();

		if (numbers_read >= k) {
			long long result = non_neg.get_sum() - non_pos.get_sum();
			cout << result << endl;
		}

		previous_number = current_number;
	}

	return 0;
}
