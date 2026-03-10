#include "PmergeMe.hpp"

#include <algorithm>
#include <iomanip>
#include <sys/time.h>
#include <utility>

// ── helpers ──────────────────────────────────────────────────────────────────

// Generate the Jacobsthal sequence: 1, 3, 5, 11, 21, 43, …
// Each entry is the upper index of an insertion group (1-based).
// We build it until the last value >= limit so all pend indices are covered.
static std::vector<size_t> makeJacobsthal(size_t limit)
{
	std::vector<size_t> j;
	j.push_back(1);
	j.push_back(3);
	while (j.back() < limit)
		j.push_back(j[j.size() - 1] + 2 * j[j.size() - 2]);
	return j;
}

// Insert `value` into `chain` using binary search within [0, bound).
// `bound` is the exclusive upper index — always the current position of the
// paired "larger" element, which is an upper bound for `value`.
static void binaryInsertVec(std::vector<int> &chain, int value, size_t bound)
{
	size_t lo = 0, hi = bound;
	while (lo < hi)
	{
		const size_t mid = lo + (hi - lo) / 2;
		if (chain[mid] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + static_cast<std::ptrdiff_t>(lo), value);
}

static void binaryInsertDeq(std::deque<int> &chain, int value, size_t bound)
{
	size_t lo = 0, hi = bound;
	while (lo < hi)
	{
		const size_t mid = lo + (hi - lo) / 2;
		if (chain[mid] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + static_cast<std::ptrdiff_t>(lo), value);
}

// ── Ford-Johnson core ─────────────────────────────────────────────────────────
//
// Algorithm outline for a sequence of n distinct integers:
//  1. If n is odd, set aside the last element (the "straggler").
//  2. Compare each consecutive pair; keep the larger element as the main chain
//     candidate and the smaller as its pend partner.
//  3. Recursively sort the main-chain candidates using Ford-Johnson.
//  4. Re-sort the (larger, smaller) pairs to match the sorted main chain.
//  5. Insert pend[0] before main[0] (it's unconditionally smaller).
//  6. Insert the remaining pend elements in the order dictated by the
//     Jacobsthal sequence.  For pend[j], binary-search is bounded by the
//     current position of main[j] in the chain, limiting comparisons.
//  7. Binary-insert the straggler into the fully assembled chain.

void PmergeMe::sortVec(std::vector<int> &seq)
{
	size_t n = seq.size();
	if (n <= 1)
		return;

	// 1 – straggler
	bool odd = n % 2 != 0;
	int straggler = 0;
	if (odd)
	{
		straggler = seq.back();
		seq.pop_back();
		--n;
	}

	// 2 – sort each pair so seq[2i] >= seq[2i+1]
	for (size_t i = 0; i + 1 < n; i += 2)
		if (seq[i] < seq[i + 1])
			std::swap(seq[i], seq[i + 1]);

	typedef std::pair<int, int> Pair;
	std::vector<Pair> pairs;
	pairs.reserve(n / 2);
	for (size_t i = 0; i < n; i += 2)
		pairs.push_back(std::make_pair(seq[i], seq[i + 1]));

	// 3 – recursively sort the larger elements
	std::vector<int> main;
	main.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i)
		main.push_back(pairs[i].first);
	sortVec(main);

	// 4 – sort pairs by their first (larger) element so pend[i] corresponds to main[i]
	std::sort(pairs.begin(), pairs.end());

	// 5 & 6 – Jacobsthal-ordered insertion
	const size_t k = pairs.size();
	const std::vector<size_t> jac = makeJacobsthal(k);
	std::vector<bool> done(k, false);

	for (size_t g = 0; g < jac.size(); ++g)
	{
		const size_t end_idx = (g == 0) ? 0 : jac[g - 1];
		const size_t start_idx = std::min(jac[g], k);
		// Insert from the top of this group downward
		for (size_t j = start_idx; j > end_idx; --j)
		{
			const size_t idx = j - 1; // convert to 0-based
			if (done[idx])
				continue;
			// Upper bound = current position of the paired larger element
			const size_t bound = static_cast<size_t>(
					std::lower_bound(main.begin(), main.end(), pairs[idx].first) - main.begin());
			binaryInsertVec(main, pairs[idx].second, bound);
			done[idx] = true;
		}
	}

	// 7 – insert straggler with an unrestricted binary search
	if (odd)
		binaryInsertVec(main, straggler, main.size());

	seq = main;
}

// Identical algorithm for std::deque — kept separate to show per-container
// performance and to use the deque-specific insert path.
void PmergeMe::sortDeq(std::deque<int> &seq)
{
	size_t n = seq.size();
	if (n <= 1)
		return;

	bool odd = n % 2 != 0;
	int straggler = 0;
	if (odd)
	{
		straggler = seq.back();
		seq.pop_back();
		--n;
	}

	for (size_t i = 0; i + 1 < n; i += 2)
		if (seq[i] < seq[i + 1])
			std::swap(seq[i], seq[i + 1]);

	typedef std::pair<int, int> Pair;
	std::vector<Pair> pairs;
	pairs.reserve(n / 2);
	for (size_t i = 0; i < n; i += 2)
		pairs.push_back(std::make_pair(seq[i], seq[i + 1]));

	std::deque<int> main;
	for (size_t i = 0; i < pairs.size(); ++i)
		main.push_back(pairs[i].first);
	sortDeq(main);

	std::sort(pairs.begin(), pairs.end());

	const size_t k = pairs.size();
	const std::vector<size_t> jac = makeJacobsthal(k);
	std::vector<bool> done(k, false);

	for (size_t g = 0; g < jac.size(); ++g)
	{
		const size_t end_idx = (g == 0) ? 0 : jac[g - 1];
		const size_t start_idx = std::min(jac[g], k);
		for (size_t j = start_idx; j > end_idx; --j)
		{
			const size_t idx = j - 1;
			if (done[idx])
				continue;
			const size_t bound = static_cast<size_t>(
					std::lower_bound(main.begin(), main.end(), pairs[idx].first) - main.begin());
			binaryInsertDeq(main, pairs[idx].second, bound);
			done[idx] = true;
		}
	}

	if (odd)
		binaryInsertDeq(main, straggler, main.size());

	seq = main;
}

// ── class implementation ──────────────────────────────────────────────────────

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int> &input) : _vec(input), _deq(input.begin(), input.end())
{
	std::set<int> seen;
	for (std::vector<int>::const_iterator it = input.begin(); it != input.end(); ++it)
	{
		if (!seen.insert(*it).second)
			throw DuplicateNumber();
	}
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
	// ── Before
	std::cout << "Before:";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	// ── Sort and time std::vector
	struct timeval ts, te;
	gettimeofday(&ts, NULL);
	sortVec(_vec);
	gettimeofday(&te, NULL);
	const double vecUs = (te.tv_sec - ts.tv_sec) * 1e6 + (te.tv_usec - ts.tv_usec);

	// ── After (from the sorted vector)
	std::cout << "After:";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	// ── Sort and time std::deque
	gettimeofday(&ts, NULL);
	sortDeq(_deq);
	gettimeofday(&te, NULL);
	const double deqUs = (te.tv_sec - ts.tv_sec) * 1e6 + (te.tv_usec - ts.tv_usec);

	// ── Timing output
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vec.size()
						<< " elements with std::vector : " << vecUs << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
						<< " elements with std::deque  : " << deqUs << " us" << std::endl;
}

const char *PmergeMe::DuplicateNumber::what() const throw()
{
	return "Error: duplicate number.";
}
