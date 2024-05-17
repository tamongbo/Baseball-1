#include <string>
#include <stdexcept>
#include <unordered_map>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	Baseball(const string& question)
		:question(question) {
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);

		GuessResult ret{ false, 0, 0 };
		bool isStrike[3] = { 0, };
			
		ret.strikes = getStrikes(guessNumber, isStrike);
	
		if (ret.strikes == 3) {
			ret.solved = true;
		}
		else {
			ret.balls = calculateBalls(guessNumber, isStrike);
		}
		return ret;
	}

	int getStrikes(const std::string& guessNumber, bool isStrike[3])
	{
		int strikeCnt = 0;
		for (int i = 0; i < 3; i++) {
			if (guessNumber[i] != question[i]) continue;
			strikeCnt++;
			isStrike[i] = true;
		}
		return strikeCnt;
	}

	int calculateBalls(const std::string& guessNumber, bool isStrike[3])
	{
		int ballCnt = 0;
		for (int i = 0; i < 3; i++) {
			if (true == isStrike[i]) continue; 
	
			for (int j = 0; j < 3; j++) {
				if (guessNumber[i] == question[j]) {
					ballCnt++;
				}
			}
		}
		return ballCnt;
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if ('0' <= ch && ch <= '9') continue;
			throw invalid_argument("Must be number.");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number.");
		}
	}

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}
private:
	string question;
};