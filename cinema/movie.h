#pragma once
#include <string>
using namespace std;

struct Movie {
    string title;
    string producer;
    string genre;
    string release_d;
    string duration;
};

extern Movie movie[5];
extern int CountMovie;
void ShowsMovie();
void CreateMovie();
void UpdateMovie();