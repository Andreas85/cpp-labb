#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

int field_width = 2;
int field_height = 3;

int trainedQMatrix[12][12] 
{
    {0, 0, 0, 0, 80, 0, 80, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 80, 0, 80, 0, 0, 0, 0},
    {0, 0, 0, 0, 80, 0, 80, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 80, 0, 80, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100},
    {0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int states[12][4]
{
    {0,0,2,0},
    {0,1,2,0},
    {0,0,2,1},
    {0,1,2,1},

    {1,0,2,0},
    {1,1,2,0},
    {1,0,2,1},
    {1,1,2,1},

    {2,0,2,0},
    {2,1,2,0},
    {2,0,2,1},
    {2,1,2,1}
};

class Object {
    public:
        int xPos;
        int yPos;
        Object (int, int);
        int get_x_pos() { return xPos; };
        int get_y_pos() { return yPos; };
        bool move_down() {
            if (yPos == field_height) {
                return false;
            }
            yPos++;
            return true;
        };
};

Object::Object (int x, int y) {
    xPos = x;
    yPos = y;
}

class Food : public Object {
    public:
        Food (int x, int y) : Object (x, y) {
            xPos = x;
            yPos = y;
        }
};

class Creature : public Object {
    public:
        Creature (int x, int y) : Object (x, y) {
            xPos = x;
            yPos = y;
        }
        void move(int newxPos) {
            xPos = newxPos;
        }
};

int main() {
    std::system("clear");
    
    srand((unsigned int)time(NULL));

    int food_eaten = 0;

    Creature creature (0, field_height - 1);

    std::vector< Food > foodVector;

    for (int r = 0; r < 1000; r++) {
        if (foodVector.size() == 0) {
            foodVector.push_back( Food (rand() % field_width, 0) );
        }
        std::system("clear");

        for (int y = 0; y < field_height; y++) {
            cout << "|";
            for (int x = 0; x < field_width; x++) {
                int outputFlag = false; 
                if (x == creature.get_x_pos() && y == creature.get_y_pos()) {
                    cout << "C ";
                    outputFlag = true;
                }

                if (!outputFlag) {
                    for (Food food : foodVector) {
                        if (x == food.get_x_pos() && y == food.get_y_pos()) {
                            cout << "F ";
                            outputFlag = true;
                        }
                    }
                }
                if (!outputFlag) {
                    cout << "  ";
                }
            }
            cout << "|" << endl; 
        }

        for (Food food : foodVector) {
            if (food.get_x_pos() == creature.get_x_pos() && food.get_y_pos() == creature.get_y_pos()) {
                food_eaten++;                
            }
        }
        
        cout << endl << "Food eaten: "<< food_eaten << endl;

        int highestIndex = 0;

        for (int a = 0; a < 12; a++) {
            if (states[a][0] == foodVector[0].get_y_pos() && states[a][1] == foodVector[0].get_x_pos() && states[a][3] == creature.get_x_pos()) {
                for (int c = 0; c < 12; c++) {
                    if (trainedQMatrix[a][c] > trainedQMatrix[a][highestIndex]) {
                        highestIndex = c;
                    }
                }
            }
        }

        for (int a = 0; a < foodVector.size(); a++) {
            if (!foodVector[a].move_down()) {
                foodVector.erase(foodVector.begin() + a);
            }
        }

        creature.move(states[highestIndex][3]);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}
