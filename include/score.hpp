#pragma once

#include <string>

class Score {
    public:
       static std::string getScore();
       static void Reset();
    private:
       static int score;
       static float startTime;
};
